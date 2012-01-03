#!/usr/bin/env ruby
#/usr/local/bin/ruby
=begin
create Makefile script for Ruby/OpenCV

usage : ruby extconf.rb
        make && make install

VC : ruby extconf.rb
     nmake
	 nmake install
=end
require "mkmf"

# option "opencv"
# extconf.rb --with-opencv-dir=/path/to/opencv

dir_config("opencv", "/usr/local/include", "/usr/local/lib")
dir_config("libxml2", "/usr/include", "/usr/lib")

opencv_headers = ["opencv2/core/core_c.h", "opencv2/core/core.hpp", "opencv2/imgproc/imgproc_c.h",
                  "opencv2/imgproc/imgproc.hpp", "opencv2/video/tracking.hpp", "opencv2/features2d/features2d.hpp",
                  "opencv2/flann/flann.hpp", "opencv2/calib3d/calib3d.hpp", "opencv2/objdetect/objdetect.hpp",
                  "opencv2/legacy/compat.hpp", "opencv2/legacy/legacy.hpp", "opencv2/highgui/highgui_c.h",
                  "opencv2/highgui/highgui.hpp"]

opencv_libraries = ["opencv_calib3d", "opencv_contrib", "opencv_core", "opencv_features2d",
                    "opencv_flann", "opencv_gpu", "opencv_highgui", "opencv_imgproc",
                    "opencv_legacy", "opencv_ml", "opencv_objdetect", "opencv_video"]


puts ">> check require libraries..."
case CONFIG["arch"]
when /mswin32/
  OPENCV_VERSION_SUFFIX = '231'
  opencv_libraries.map! {|lib| lib + OPENCV_VERSION_SUFFIX }
  have_library("msvcrt")
  opencv_libraries.each{|lib|
    raise "#{lib}.lib not found." unless have_library(lib)
  }
  $CFLAGS << ' /EHsc'
else
  opencv_libraries.each{|lib|
    raise "lib#{lib} not found." unless have_library(lib)
  }
  #have_library("ml")
  have_library("stdc++")
end

# check require headers
puts ">> check require headers..."
opencv_headers.each{|header|
  raise "#{header} not found." unless have_header(header)
}
#have_header("ml.h")
have_header("stdarg.h")

# check require functions.
# todo

# Quick fix for 1.8.7
$CFLAGS << " -I#{File.dirname(__FILE__)}/ext/opencv"

# step-final. create Makefile
create_makefile("opencv", "./ext/opencv")

