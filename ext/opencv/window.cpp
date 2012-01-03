/************************************************************

   window.cpp -

   $Author: lsxi $

   Copyright (C) 2005-2006 Masakazu Yonekura

************************************************************/
#include "window.h"
/*
 * Document-class: OpenCV::GUI::Window
 *
 * Simple Window wedget. Window can show image(CvMat/IplImage).
 *
 * view image sample:
 *   image = OpenCV::IplImage::load("opencv.bmp")     #=> load image
 *   window = OpenCV::GUI::Window.new("simple viewer")#=> create new window named "simaple viewer"
 *   window.show(image)                               #=> show image
 */
__NAMESPACE_BEGIN_OPENCV
__NAMESPACE_BEGIN_GUI
__NAMESPACE_BEGIN_WINDOW

const char*
GET_WINDOW_NAME(VALUE object)
{
  void *handle = DATA_PTR(object);
  if (!handle)
    rb_raise(rb_eStandardError, "window handle error");
  char* window_name = NULL;
  try {
    window_name = (char*)cvGetWindowName(handle);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return (const char*)window_name;
}

st_table *windows = st_init_numtable();

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
   * GUI = rb_define_module_under(opencv, "GUI");         
   *
   * note: this comment is used by rdoc.
   */
  VALUE GUI = rb_module_GUI();
  rb_klass = rb_define_class_under(GUI, "Window", rb_cObject);
  rb_define_singleton_method(rb_klass, "[]", RUBY_METHOD_FUNC(rb_aref), 1);
  rb_define_private_method(rb_klass, "initialize", RUBY_METHOD_FUNC(rb_initialize), -1);
  rb_define_method(rb_klass, "alive?", RUBY_METHOD_FUNC(rb_alive_q), 0);
  rb_define_method(rb_klass, "destroy", RUBY_METHOD_FUNC(rb_destroy), 0);
  rb_define_singleton_method(rb_klass, "destroy_all", RUBY_METHOD_FUNC(rb_destroy_all), 0);
  rb_define_method(rb_klass, "resize", RUBY_METHOD_FUNC(rb_resize), -1);
  rb_define_method(rb_klass, "move", RUBY_METHOD_FUNC(rb_move), -1);
  rb_define_method(rb_klass, "show_image", RUBY_METHOD_FUNC(rb_show_image), -1);
  rb_define_alias(rb_klass, "show", "show_image");
  rb_define_method(rb_klass, "set_trackbar", RUBY_METHOD_FUNC(rb_set_trackbar), -1);
  rb_define_method(rb_klass, "set_mouse_callback", RUBY_METHOD_FUNC(rb_set_mouse_callback), -1);
  rb_define_alias(rb_klass, "on_mouse", "set_mouse_callback");
}

VALUE
rb_allocate(VALUE klass)
{
  return Data_Wrap_Struct(klass, mark, free, 0);
}

void
mark(void *ptr)
{
  st_table *holder;
  if (st_lookup(windows, (st_data_t)ptr, (st_data_t*)&holder)) {
    st_foreach(holder, (int (*)(ANYARGS))each_protect, 0);
  }
}

VALUE
each_protect(VALUE key, VALUE value)
{
  rb_gc_mark(value);
  return ST_CONTINUE;
}

void
free(void *ptr)
{
  cvFree(&ptr);
}

/*
 * call-seq:
 *   [<i>name</i>]
 *
 * Return window named <i>name</i> if exist, otherwise nil.
 */
VALUE
rb_aref(VALUE klass, VALUE name)
{
  VALUE window;
  Check_Type(name, T_STRING);
  void *handle = NULL;
  try {
    handle = cvGetWindowHandle(StringValueCStr(name));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  st_table *holder;
  if (st_lookup(windows, (st_data_t)handle, (st_data_t*)&holder) && 
      st_lookup(holder, 0, (st_data_t*)&window)) {
    return window;
  }
  return Qnil;
}

/*
 * call-seq:
 *   new(<i>name[,flags]</i>)
 *
 * Create new window named <i>name</i>.
 * If <i>flags</i> is CV_WINDOW_AUTOSIZE (default), window size automatically resize when image given.
 */
VALUE
rb_initialize(int argc, VALUE *argv, VALUE self)
{
  VALUE name, flags;
  rb_scan_args(argc, argv, "11", &name, &flags);
  Check_Type(name, T_STRING);
  int mode = CV_WINDOW_AUTOSIZE;
  if (argc == 2) {
    Check_Type(flags, T_FIXNUM);
    mode = FIX2INT(flags);
  }

  char* name_str = StringValueCStr(name);
  void *handle = NULL;
  try {
    cvNamedWindow(name_str, mode);
    handle = cvGetWindowHandle(name_str);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  if (st_lookup(windows, (st_data_t)handle, 0)) {
    rb_raise(rb_eStandardError, "window name should be unique.");
  }
  DATA_PTR(self) = handle;
  st_table *holder = st_init_numtable();
  st_insert(holder, (st_data_t)0, (st_data_t)self);
  st_insert(windows, (st_data_t)handle, (st_data_t)holder);
  return self;
}

/*
 * Return alive status of window. Return true if alive, otherwise return false.
 */
VALUE
rb_alive_q(VALUE self)
{
  if (st_lookup(windows, (st_data_t)DATA_PTR(self), 0)) {
    return Qtrue;
  }
  return Qfalse;
}

/*
 * Destroys a window. alive status of window be false.
 */
VALUE
rb_destroy(VALUE self)
{
  void *handle = DATA_PTR(self);
  st_table *holder;
  if (st_delete(windows, (st_data_t*)&handle, (st_data_t*)&holder)) {
    st_free_table(holder);
  }
  try {
    cvDestroyWindow(GET_WINDOW_NAME(self));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

/*
 * Destorys all the windows.
 */
VALUE
rb_destroy_all(VALUE klass)
{
  st_free_table(windows);
  windows = st_init_numtable();
  try {
    cvDestroyAllWindows();
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return Qnil;
}

/*
 * call-seq:
 *   resize(<i>size</i>)
 *   resize(<i>width, height</i>)
 *
 * Set window size.
 */
VALUE
rb_resize(int argc, VALUE *argv, VALUE self)
{
  CvSize size;
  switch (argc) {
  case 1:
    size = VALUE_TO_CVSIZE(argv[0]);
    break;
  case 2:
    size = cvSize(NUM2INT(argv[0]), NUM2INT(argv[1]));
    break;
  default:
    rb_raise(rb_eArgError, "wrong number of arguments (1 or 2)");
    break;
  }
  try {
    cvResizeWindow(GET_WINDOW_NAME(self), size.width, size.height);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

/*
 * call-seq:
 *   move(<i>point</i>)
 *   move(<i>x, y</i>)
 *
 * Set window position.
 */
VALUE
rb_move(int argc, VALUE *argv, VALUE self)
{
  CvPoint point;
  switch (argc) {
  case 1:
    point = VALUE_TO_CVPOINT(argv[0]);
    break;
  case 2:
    point = cvPoint(FIX2INT(argv[0]), FIX2INT(argv[1]));
    break;
  default:
    rb_raise(rb_eArgError, "wrong number of arguments (1 or 2)");
    break;
  }
  try {
    cvMoveWindow(GET_WINDOW_NAME(self), point.x, point.y);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}
      
/*
 * call-seq:
 *   show_image(<i>image</i>)
 *
 * Show the image. If the window was created with <i>flags</i> = CV_WINDOW_AUTOSIZE then the image is shown
 * with its original size, otherwize the image is scaled to fit the window.
 */
VALUE
rb_show_image(int argc, VALUE *argv, VALUE self)
{
  CvArr* image = NULL;
  if (argc > 0) {
    image = CVARR_WITH_CHECK(argv[0]);
    st_table *holder;
    if (st_lookup(windows, (st_data_t)DATA_PTR(self), (st_data_t*)&holder))
      st_insert(holder, cCvMat::rb_class(), argv[0]);
    else
      rb_raise(rb_eFatal, "invalid window operation.");
  }
  try {
    cvShowImage(GET_WINDOW_NAME(self), image);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  return self;
}

void
trackbar_callback(int value, void* block)
{
  rb_funcall((VALUE)block, rb_intern("call"), 1, INT2NUM(value));
}

/*
 * call-seq:
 *   set_trackbar(<i>trackbar</i>)
 *   set_trackbar(<i>name,maxval[,val],&block</i>)
 *   set_trackbar(<i>name,maxval[,val]</i>){|value| ... }
 *
 * Create Trackbar on this window. Return new Trackbar.
 * see Trackbar.new
 */
VALUE
rb_set_trackbar(int argc, VALUE *argv, VALUE self)
{
  VALUE instance;
  if (argc == 1 && rb_obj_is_kind_of(argv[0], cTrackbar::rb_class())) {
    instance = argv[0];
  }
  else {
    instance = cTrackbar::rb_initialize(argc, argv, cTrackbar::rb_allocate(cTrackbar::rb_class()));
  }
  Trackbar *trackbar = TRACKBAR(instance);
  try {
    cv::createTrackbar(trackbar->name, GET_WINDOW_NAME(self), &(trackbar->val), trackbar->maxval,
		       (cv::TrackbarCallback)trackbar_callback, (void*)(trackbar->block));
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  st_table *holder;
  if (st_lookup(windows, (st_data_t)DATA_PTR(self), (st_data_t*)&holder)) {
    st_insert(holder, (st_data_t)&trackbar->name, (st_data_t)instance);
  }
  return instance;
}

void
on_mouse(int event, int x, int y, int flags, void* param)
{
  VALUE block = (VALUE)param;
  if (rb_obj_is_kind_of(block, rb_cProc))
    rb_funcall(block, rb_intern("call"), 1, cMouseEvent::new_object(event, x, y, flags));
}

/*
 * call-seq:
 *   set_mouse_callback(&block)
 *   set_mouse_callback {|| ... }
 *
 * Set mouse callback.
 * When the mouse is operated on the window, block will be called.
 * Return Proc object.
 * block given mouse event object, see GUI::Window::MouseEvent
 *
 * e.g. display mouse event on console.
 *   window = OpenCV::GUI::Window.new "sample window"
 *   image = OpenCV::IplImage::load "sample.png"
 *   window.show(image)
 *   window.set_mouse_callback {|mouse|  
 *     e = "#{mouse.x}, #{mouse.y} : #{mouse.event} : "
 *     e << "<L>" if mouse.left_button?
 *     e << "<R>" if mouse.right_button?
 *     e << "<M>" if mouse.middle_button?
 *     e << "[CTRL]" if mouse.ctrl_key?
 *     e << "[SHIFT]" if mouse.shift_key?
 *     e << "[ALT]" if mouse.alt_key?
 *     puts e
 *   }
 *   OpenCV::GUI::wait_key
 */
VALUE
rb_set_mouse_callback(int argc, VALUE* argv, VALUE self)
{
  if (!rb_block_given_p())
    rb_raise(rb_eArgError, "block not given.");

  VALUE block = Qnil;
  rb_scan_args(argc, argv, "0&", &block);
  try {
    cvSetMouseCallback(GET_WINDOW_NAME(self), on_mouse, (void*)block);
  }
  catch (cv::Exception& e) {
    raise_cverror(e);
  }
  st_table *holder;
  if (st_lookup(windows, (st_data_t)DATA_PTR(self), (st_data_t*)&holder)) {
    st_insert(holder, rb_cProc, block);
  }
  else {
    rb_raise(rb_eStandardError, "window is destroied.");
  }
  return block;
}

__NAMESPACE_END_WINDOW
__NAMESPACE_END_GUI
__NAMESPACE_END_OPENCV

