#!/usr/bin/env ruby
=begin
create Makefile script for Ruby/OpenCV

usage : ruby extconf.rb
        make && make install

VC : ruby extconf.rb
     nmake
	 nmake install
=end
require "mkmf"

dir_config("opencv", "/usr/local/include", "/usr/local/lib")
dir_config("libxml2", "/usr/include", "/usr/lib")

opencv_headers = ["opencv/cv.h", "opencv/cv.hpp", "opencv/cvaux.h",
                  "opencv/cvaux.hpp", "opencv/cxcore.h", "opencv/cxcore.hpp",
                  "opencv/highgui.h", "opencv/highgui.hpp"]
opencv_libraries = ["cv", "cvaux", "cxcore", "highgui"]

puts ">> Check the required libraries..."

OPENCV_VERSION_SUFFIX = '210'
case CONFIG["arch"]
when /mswin32/
  opencv_libraries.map! {|lib| lib + OPENCV_VERSION_SUFFIX }
  have_library("msvcrt")
  opencv_libraries.each {|lib|
    raise "#{lib}.lib not found." unless have_library(lib)
  }
  $CFLAGS << ' /EHsc'
when /mingw32/
  opencv_libraries.map! {|lib| lib + OPENCV_VERSION_SUFFIX }
  have_library("msvcrt")
  opencv_libraries.each {|lib|
    raise "lib#{lib} not found." unless have_library(lib)
  }
else
  opencv_libraries.each {|lib|
    raise "lib#{lib} not found." unless have_library(lib)
  }
  have_library("stdc++")
end

# Check the required headers
puts ">> Check the required headers..."
opencv_headers.each {|header|
  raise "#{header} not found." unless have_header(header)
}
have_header("stdarg.h")

# Quick fix for 1.8.7
$CFLAGS << " -I#{File.dirname(__FILE__)}/ext/opencv"

# Create Makefile
create_makefile("opencv", "./ext/opencv")

