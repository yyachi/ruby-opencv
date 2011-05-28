#!/usr/bin/env ruby
# -*- mode: ruby; coding: utf-8-unix -*- 
require 'test/unit'
require 'opencv'
require File.expand_path(File.dirname(__FILE__)) + '/helper'

include OpenCV

# Tests for OpenCV::CvCapture
class TestCvCapture < OpenCVTestCase
  def setup
    @cap = CvCapture.open(AVI_SAMPLE)
  end

  def teardown
    @cap = nil
  end

  def test_INTERFACE
    assert_equal(CvCapture::INTERFACE[:any], 0)
    assert_equal(CvCapture::INTERFACE[:mil], 100)
    assert_equal(CvCapture::INTERFACE[:vfw], 200)
    assert_equal(CvCapture::INTERFACE[:v4l], 200)
    assert_equal(CvCapture::INTERFACE[:v4l2], 200)
    assert_equal(CvCapture::INTERFACE[:fireware], 300)
    assert_equal(CvCapture::INTERFACE[:ieee1394], 300)
    assert_equal(CvCapture::INTERFACE[:dc1394], 300)
    assert_equal(CvCapture::INTERFACE[:cmu1394], 300)
    assert_equal(CvCapture::INTERFACE[:stereo], 400)
    assert_equal(CvCapture::INTERFACE[:tyzx], 400)
    assert_equal(CvCapture::INTERFACE[:tyzx_left], 400)
    assert_equal(CvCapture::INTERFACE[:tyzx_right], 401)
    assert_equal(CvCapture::INTERFACE[:tyzx_color], 402)
    assert_equal(CvCapture::INTERFACE[:tyzx_z], 403)
    assert_equal(CvCapture::INTERFACE[:qt], 500)
    assert_equal(CvCapture::INTERFACE[:quicktime], 500)
  end

  def test_open
    cap1 = CvCapture.open(AVI_SAMPLE)
    assert_equal(CvCapture, cap1.class)

    # Uncomment the following lines to test capturing from camera
    # cap2 = CvCapture.open(0)
    # assert_equal(CvCapture, cap2.class)
    # CvCapture::INTERFACE.each { |k, v|
    #   cap3 = CvCapture.open(k)
    #   assert_equal(CvCapture, cap3.class)
    # }
  end

  def test_grab
    assert(@cap.grab)
  end

  def test_retrieve
    @cap.grab
    img = @cap.retrieve
    assert_equal(IplImage, img.class)
  end

  def test_query
    img = @cap.query
    assert_equal(IplImage, img.class)
  end

  def test_millisecond
    assert(@cap.millisecond.is_a? Numeric)
  end

  def test_frames
    assert(@cap.frames.is_a? Numeric)
  end

  def test_avi_ratio
    assert(@cap.avi_ratio.is_a? Numeric)
  end

  def test_size
    assert_equal(CvSize, @cap.size.class)
  end

  def test_width
    assert(@cap.width.is_a? Numeric)
  end

  def test_height
    assert(@cap.height.is_a? Numeric)
  end

  def test_fps
    assert(@cap.fps.is_a? Numeric)
  end

  def test_fourcc
    assert_equal(String, @cap.fourcc.class)
  end

  def test_frame_count
    assert(@cap.frame_count.is_a? Numeric)
  end

  def test_format
    assert(@cap.format.is_a? Numeric)
  end

  def test_mode
    assert(@cap.mode.is_a? Numeric)
  end

  def test_brightness
    assert(@cap.brightness.is_a? Numeric)
  end

  def test_contrast
    assert(@cap.contrast.is_a? Numeric)
  end

  def test_saturation
    assert(@cap.saturation.is_a? Numeric)
  end

  def test_hue
    assert(@cap.hue.is_a? Numeric)
  end

  def test_gain
    assert(@cap.gain.is_a? Numeric)
  end

  def test_exposure
    assert(@cap.exposure.is_a? Numeric)
  end

  def test_convert_rgb
    assert((@cap.convert_rgb == true) ||
           (@cap.convert_rgb == false))
  end

  def test_white_balance
    assert(@cap.white_balance.is_a? Numeric)
  end

  def test_rectification
    assert(@cap.rectification.is_a? Numeric)
  end
end

