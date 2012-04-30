/************************************************************

   cvchain.cpp -

   $Author: lsxi $

   Copyright (C) 2007 Masakazu Yonekura

************************************************************/
#include "cvchain.h"
/*
 * Document-class: OpenCV::CvChain
 *
 * Freeman chain code
 */
__NAMESPACE_BEGIN_OPENCV
__NAMESPACE_BEGIN_CVCHAIN

#define APPROX_CHAIN_OPTION(op) rb_get_option_table(rb_klass, "APPROX_CHAIN_OPTION", op)
#define APPROX_CHAIN_METHOD(op) CVMETHOD("APPROX_CHAIN_METHOD", LOOKUP_CVMETHOD(op, "method"), CV_CHAIN_APPROX_SIMPLE)
#define APPROX_CHAIN_PARAMETER(op) NUM2INT(LOOKUP_CVMETHOD(op, "parameter"))
#define APPROX_CHAIN_MINIMAL_PARAMETER(op) NUM2INT(LOOKUP_CVMETHOD(op, "minimal_parameter"))
#define APPROX_CHAIN_RECURSIVE(op) TRUE_OR_FALSE(LOOKUP_CVMETHOD(op, "recursive"))

VALUE rb_klass;

VALUE
rb_class()
{
  return rb_klass;
}

void
define_ruby_class()
{
  if (rb_klass)
    return;
  /* 
   * opencv = rb_define_module("OpenCV");
   * cvseq = rb_define_class_under(opencv, "CvSeq");
   * curve = rb_define_module_under(opencv, "Curve");
   * note: this comment is used by rdoc.
   */
  VALUE opencv = rb_module_opencv();
  VALUE cvseq = cCvSeq::rb_class();
  VALUE curve = mCurve::rb_module();

  rb_klass = rb_define_class_under(opencv, "CvChain", cvseq);
  rb_include_module(rb_klass, curve);
  VALUE approx_chain_option = rb_hash_new();
  rb_define_const(rb_klass, "APPROX_CHAIN_OPTION", approx_chain_option); 
  rb_hash_aset(approx_chain_option, ID2SYM(rb_intern("method")), ID2SYM(rb_intern("approx_simple")));
  rb_hash_aset(approx_chain_option, ID2SYM(rb_intern("parameter")), rb_float_new(0));
  rb_hash_aset(approx_chain_option, ID2SYM(rb_intern("minimal_parameter")), INT2FIX(0));
  rb_hash_aset(approx_chain_option, ID2SYM(rb_intern("recursive")), Qfalse);

  rb_define_private_method(rb_klass, "initialize", RUBY_METHOD_FUNC(rb_initialize), -1);
  rb_define_method(rb_klass, "origin", RUBY_METHOD_FUNC(rb_origin), 0);
  rb_define_method(rb_klass, "origin=", RUBY_METHOD_FUNC(rb_set_origin), 1);
  rb_define_method(rb_klass, "codes", RUBY_METHOD_FUNC(rb_codes), 0);
  rb_define_method(rb_klass, "points", RUBY_METHOD_FUNC(rb_points), 0);
  rb_define_method(rb_klass, "approx_chain", RUBY_METHOD_FUNC(rb_approx_chain), -1);
  rb_define_alias(rb_klass, "approx", "approx_chain");
}

VALUE
rb_allocate(VALUE klass)
{
  CvChain *ptr;
  return Data_Make_Struct(klass, CvChain, 0, 0, ptr);
}

/*
 * Create a new chain code
 * @scope class
 * @overload new(storage=nil)
 *   @param storage [CvMemStorage,nil] Sequence location (If storage is nil, allocates a new storage automatically)
 * @return [CvChain] New CvChain instance
 * @opencv_func cvCreateSeq (seq_flags=CV_SEQ_ELTYPE_CODE)
 */
VALUE
rb_initialize(int argc, VALUE *argv, VALUE self)
{
  CvMemStorage *storage;
  VALUE storage_value;
  if (rb_scan_args(argc, argv, "01", &storage_value) > 0) {
    storage_value = CHECK_CVMEMSTORAGE(storage_value);
    storage = CVMEMSTORAGE(storage_value);
  }
  else
    storage = rb_cvCreateMemStorage(0);
  try {
    DATA_PTR(self) = (CvChain*)cvCreateSeq(CV_SEQ_ELTYPE_CODE, sizeof(CvChain),
					   sizeof(char), storage);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

/*
 * Returns Freeman chain code origin
 * @overload origin
 * @return [CvPoint] Origin of the chain code
 */
VALUE
rb_origin(VALUE self)
{
  return cCvPoint::new_object(CVCHAIN(self)->origin);
}

/*
 * Set Freeman chain code origin
 * @overload origin=value
 *   @param value [CvPoint] Origin of the chain code
 * @return [CvChain] self
 */
VALUE
rb_set_origin(VALUE self, VALUE origin)
{
  CVCHAIN(self)->origin = VALUE_TO_CVPOINT(origin);  
  return self;
}

/*
 * Returns the chain codes
 * @overload codes
 * @return [Array<Fixnum>] Chain codes
 * @opencv_func cvStartReadChainPoints
 * @opencv_func CV_READ_SEQ_ELEM
 */
VALUE
rb_codes(VALUE self)
{
  CvChain *chain = CVCHAIN(self);
  CvChainPtReader reader;
  int total = chain->total;
  VALUE ary = rb_ary_new2(total);
  try {
    cvStartReadChainPoints(chain, &reader);
    for (int i = 0; i < total; ++i) {
      CV_READ_SEQ_ELEM(reader.code, (*((CvSeqReader*)&(reader))));
      rb_ary_store(ary, i, CHR2FIX(reader.code));
    }
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return ary;
}

/*
 * Returns the points of the chain codes
 * @overload points
 * @return [Array<CvPoint>] Points of the chain codes
 * @opencv_func cvStartReadChainPoints
 * @opencv_func CV_READ_CHAIN_POINT
 */
VALUE
rb_points(VALUE self)
{
  CvChain *chain = CVCHAIN(self);
  CvChainPtReader reader;
  CvPoint p = chain->origin;
  int total = chain->total;
  VALUE ary = rb_ary_new2(total);
  try {
    cvStartReadChainPoints(chain, &reader);
    for (int i = 0; i < total; ++i) {
      CV_READ_CHAIN_POINT(p, reader);
      rb_ary_store(ary, i, cCvPoint::new_object(p));
    }
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return ary;
}

/*
 * Approximates Freeman chains with a polygonal curve
 * @overload approx_chain(options)
 *   @param options [Hash] Parameters
 *   @option options [Symbol] :method Approximation method (see the description of CvMat#find_contours)
 *   @option options [Number] :minimal_perimeter Approximates only those contours whose perimeters
 *     are not less than minimal_perimeter. Other chains are removed from the resulting structure.
 *   @option options [Boolean] :recursive Recursion flag. If it is true, the function approximates
 *     all chains that can be obtained from chain by using the h_next or v_next links.
 *     Otherwise, the single input chain is approximated.
 * @return [Array<CvPoint>] Polygonal curve
 * @opencv_func cvApproxChains
 */
VALUE
rb_approx_chain(int argc, VALUE *argv, VALUE self)
{
  VALUE approx_chain_option, storage;
  rb_scan_args(argc, argv, "01", &approx_chain_option);
  approx_chain_option = APPROX_CHAIN_OPTION(approx_chain_option);
  /* can't compile VC
     storage = cCvMemStorage::new_object();
     CvSeq *seq = cvApproxChains(CVSEQ(self), CVMEMSTORAGE(storage),
     APPROX_CHAIN_METHOD(approx_chain_option),
     APPROX_CHAIN_PARAMETER(approx_chain_option),
     APPROX_CHAIN_MINIMAL_PARAMETER(approx_chain_option),
     APPROX_CHAIN_RECURSIVE(approx_chain_option));

     return cCvSeq::new_sequence(cCvContour::rb_class(), seq, cCvPoint::rb_class(), storage);
  */
  return Qnil;
}

VALUE
new_object()
{
  VALUE storage = cCvMemStorage::new_object();
  CvSeq *seq = NULL;
  try {
    seq = cvCreateSeq(CV_SEQ_CHAIN_CONTOUR, sizeof(CvChain), sizeof(char), CVMEMSTORAGE(storage));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return cCvSeq::new_sequence(cCvChain::rb_class(), seq, T_FIXNUM, storage);
}

__NAMESPACE_END_CVCHAIN
__NAMESPACE_END_OPENCV
