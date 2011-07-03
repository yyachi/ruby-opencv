/************************************************************

  cvutils.cpp -

  $Author: ser1zw $

  Copyright (C) 2011 ser1zw

************************************************************/
#include "cvutils.h"

void
raise_typeerror(VALUE object, VALUE expected_class) {
  rb_raise(rb_eTypeError, "wrong argument type %s (expected %s)",
  	   rb_obj_classname(object), rb_class2name(expected_class));
}

void
raise_compatible_typeerror(VALUE object, VALUE expected_class) {
  rb_raise(rb_eTypeError, "wrong argument type %s (expected %s or compatible object)",
  	   rb_obj_classname(object), rb_class2name(expected_class));
}

/*
 * Allocates a memory buffer
 * When memory allocation is failed, run GC and retry it
 */
void*
rb_cvAlloc(size_t size)
{
  void* ptr = NULL;
  try {
    ptr = cvAlloc(size);
  }
  catch(cv::Exception& e) {
    if (e.code != CV_StsNoMem)
      rb_raise(rb_eRuntimeError, "%s", e.what());

    rb_gc_start();
    try {
      ptr = cvAlloc(size);
    }
    catch (cv::Exception& e) {
      if (e.code == CV_StsNoMem)
	rb_raise(rb_eNoMemError, "%s", e.what());
      else
	rb_raise(rb_eRuntimeError, "%s", e.what());
    }
  }
  return ptr;
}

/*
 * Creates CvMat and underlying data
 * When memory allocation is failed, run GC and retry it
 */
CvMat*
rb_cvCreateMat(int height, int width, int type)
{
  CvMat* ptr = NULL;
  try {
    ptr = cvCreateMat(height, width, type);
  }
  catch(cv::Exception& e) {
    if (e.code != CV_StsNoMem)
      rb_raise(rb_eRuntimeError, "%s", e.what());

    rb_gc_start();
    try {
      ptr = cvCreateMat(height, width, type);
    }
    catch (cv::Exception& e) {
      if (e.code == CV_StsNoMem)
	rb_raise(rb_eNoMemError, "%s", e.what());
      else
	rb_raise(rb_eRuntimeError, "%s", e.what());
    }
  }
  return ptr;
}

/*
 * Create IplImage header and allocate underlying data
 * When memory allocation is failed, run GC and retry it
 */
IplImage*
rb_cvCreateImage(CvSize size, int depth, int channels)
{
  IplImage* ptr = NULL;
  try {
    ptr = cvCreateImage(size, depth, channels);
  }
  catch(cv::Exception& e) {
    if (e.code != CV_StsNoMem)
      rb_raise(rb_eRuntimeError, "%s", e.what());

    rb_gc_start();
    try {
      ptr = cvCreateImage(size, depth, channels);
    }
    catch (cv::Exception& e) {
      if (e.code == CV_StsNoMem)
	rb_raise(rb_eNoMemError, "%s", e.what());
      else
	rb_raise(rb_eRuntimeError, "%s", e.what());
    }
  }
  return ptr;
}

/*
 * Creates a structuring element
 * When memory allocation is failed, run GC and retry it
 */
IplConvKernel*
rb_cvCreateStructuringElementEx(int cols, int rows,
				int anchorX, int anchorY,
				int shape, int *values)
{
  IplConvKernel* ptr = NULL;
  try {
    ptr = cvCreateStructuringElementEx(cols, rows, anchorX, anchorY, shape, values);
  }
  catch(cv::Exception& e) {
    if (e.code != CV_StsNoMem)
      rb_raise(rb_eRuntimeError, "%s", e.what());

    rb_gc_start();
    try {
      ptr = cvCreateStructuringElementEx(cols, rows, anchorX, anchorY, shape, values);
    }
    catch (cv::Exception& e) {
      if (e.code == CV_StsNoMem)
	rb_raise(rb_eNoMemError, "%s", e.what());
      else
	rb_raise(rb_eRuntimeError, "%s", e.what());
    }
  }
  return ptr;
}

/*
 * Creates memory storage
 * When memory allocation is failed, run GC and retry it
 */
CvMemStorage*
rb_cvCreateMemStorage(int block_size)
{
  CvMemStorage* ptr = NULL;
  try {
    ptr = cvCreateMemStorage(block_size);
  }
  catch(cv::Exception& e) {
    if (e.code != CV_StsNoMem)
      rb_raise(rb_eRuntimeError, "%s", e.what());

    rb_gc_start();
    try {
      ptr = cvCreateMemStorage(block_size);
    }
    catch (cv::Exception& e) {
      if (e.code == CV_StsNoMem)
	rb_raise(rb_eNoMemError, "%s", e.what());
      else
	rb_raise(rb_eRuntimeError, "%s", e.what());
    }
  }
  return ptr;
}

