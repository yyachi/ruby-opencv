#!/usr/bin/env ruby
# -*- mode: ruby; coding: utf-8-unix -*- 
require 'test/unit'
require 'opencv'
require File.expand_path(File.dirname(__FILE__)) + '/helper'

include OpenCV

# Tests for OpenCV::CvVideoWriter
class TestCvVideoWriter < OpenCVTestCase
  def test_initialize
    vw = CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(320, 240))
    assert_equal(CvVideoWriter, vw.class)
    vw.close

    vw = CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(320, 240), false)
    assert_equal(CvVideoWriter, vw.class)
    vw.close

    ## Supported only Windows(?)
    # vw = CvVideoWriter.new('foo.avi', nil, 15, CvSize.new(320, 240), false)
    # assert_equal(CvVideoWriter, vw.class)
    # vw.close

    CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(320, 240)) { |vw|
      assert_equal(CvVideoWriter, vw.class)      
    }

    assert_raise(TypeError) {
      vw = CvVideoWriter.new(123, 'MJPG', 15, CvSize.new(320, 240), false)
    }
  end

  def test_write
    vw = CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(256, 256))
    vw.write CvMat.load(FILENAME_LENA256x256)
    vw.close

    CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(256, 256)) { |vw|
      vw.write CvMat.load(FILENAME_LENA256x256)
    }
  end

  def test_close
    vw = CvVideoWriter.new('foo.avi', 'MJPG', 15, CvSize.new(320, 240))
    vw.close
  end
end

