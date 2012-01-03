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

opencv_headers = ["opencv/cv.h", "opencv/cv.hpp", "opencv/cvaux.h",
                  "opencv/cvaux.hpp", "opencv/cxcore.h", "opencv/cxcore.hpp",
                  "opencv/highgui.h", "opencv/highgui.hpp"]
opencv_libraries = ["cv", "cvaux", "cxcore", "highgui"]

puts ">> check require libraries..."
case CONFIG["arch"]
when /mswin32/
  OPENCV_VERSION_SUFFIX = '210'
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

