# -*- encoding: utf-8 -*-

Gem::Specification.new do |s|
  s.name = %q{opencv}
  s.version = "0.0.6"

  s.required_rubygems_version = Gem::Requirement.new("> 1.3.1") if s.respond_to? :required_rubygems_version=
  s.authors = ["lsxi", "ser1zw", "pcting"]
  s.date = %q{2011-04-16}
  s.description = %q{OpenCV wrapper for Ruby
}
  s.email = ["masakazu.yonekura@gmail.com", "", "pcting@gmail.com"]
  s.extensions = ["extconf.rb"]
  s.extra_rdoc_files = ["History.txt", "License.txt", "Manifest.txt"]
  s.files = ["History.txt", "License.txt", "Manifest.txt", "README.rdoc", "Rakefile", "examples/convexhull.rb", "examples/snake.rb", "examples/inpaint.png", "examples/paint.rb", "examples/contours", "examples/contours/contour_retrieval_modes.rb", "examples/contours/rotated-boxes.jpg", "examples/contours/bitmap-contours.png", "examples/contours/bitmap-contours-with-labels.png", "examples/contours/bounding-box-detect-canny.rb", "examples/stuff.jpg", "examples/face_detect.rb", "examples/inpaint.rb", "examples/houghcircle.rb", "ext/opencv", "ext/opencv/mouseevent.cpp", "ext/opencv/cvcircle32f.h", "ext/opencv/cvsurfparams.cpp", "ext/opencv/cvrect.cpp", "ext/opencv/cvsurfpoint.h", "ext/opencv/cvmoments.h", "ext/opencv/cvtermcriteria.cpp", "ext/opencv/cvconvexitydefect.cpp", "ext/opencv/cvmatnd.cpp", "ext/opencv/cvavgcomp.cpp", "ext/opencv/cvconvexitydefect.h", "ext/opencv/cvseq.cpp", "ext/opencv/cvchain.cpp", "ext/opencv/cvseq.h", "ext/opencv/opencv.cpp", "ext/opencv/cvtwopoints.cpp", "ext/opencv/cvscalar.cpp", "ext/opencv/cvsparsemat.cpp", "ext/opencv/cvfont.cpp", "ext/opencv/cvpoint3d32f.h", "ext/opencv/curve.cpp", "ext/opencv/cvutils.cpp", "ext/opencv/iplimage.cpp", "ext/opencv/mouseevent.h", "ext/opencv/cvrect.h", "ext/opencv/cvsurfparams.h", "ext/opencv/trackbar.cpp", "ext/opencv/window.cpp", "ext/opencv/cvcondensation.h", "ext/opencv/opencv.h", "ext/opencv/cvsize.cpp", "ext/opencv/pointset.cpp", "ext/opencv/cvcontour.h", "ext/opencv/cvvideowriter.h", "ext/opencv/pointset.h", "ext/opencv/cvconnectedcomp.h", "ext/opencv/cvcircle32f.cpp", "ext/opencv/cvvideowriter.cpp", "ext/opencv/cvavgcomp.h", "ext/opencv/cverror.cpp", "ext/opencv/cvsize2d32f.cpp", "ext/opencv/cvpoint2d32f.h", "ext/opencv/cvcontour.cpp", "ext/opencv/cvmat.cpp", "ext/opencv/cvmemstorage.cpp", "ext/opencv/lib", "ext/opencv/lib/opencv", "ext/opencv/lib/opencv/version.rb", "ext/opencv/lib/opencv.rb", "ext/opencv/cvsurfpoint.cpp", "ext/opencv/cvfont.h", "ext/opencv/curve.h", "ext/opencv/cvslice.h", "ext/opencv/cvhumoments.h", "ext/opencv/cvhumoments.cpp", "ext/opencv/cvline.h", "ext/opencv/cvhaarclassifiercascade.cpp", "ext/opencv/gui.h", "ext/opencv/cvsize2d32f.h", "ext/opencv/cvutils.h", "ext/opencv/gui.cpp", "ext/opencv/cvmemstorage.h", "ext/opencv/cvchain.h", "ext/opencv/cvbox2d.h", "ext/opencv/cvmoments.cpp", "ext/opencv/cvscalar.h", "ext/opencv/cvsparsemat.h", "ext/opencv/cvhistogram.h", "ext/opencv/cvpoint.h", "ext/opencv/cvslice.cpp", "ext/opencv/cvcontourtree.h", "ext/opencv/cvline.cpp", "ext/opencv/cverror.h", "ext/opencv/cvcontourtree.cpp", "ext/opencv/cvcondensation.cpp", "ext/opencv/iplimage.h", "ext/opencv/cvpoint.cpp", "ext/opencv/cvbox2d.cpp", "ext/opencv/iplconvkernel.h", "ext/opencv/cvcapture.cpp", "ext/opencv/cvconnectedcomp.cpp", "ext/opencv/cvtwopoints.h", "ext/opencv/cvpoint3d32f.cpp", "ext/opencv/cvhaarclassifiercascade.h", "ext/opencv/cvhistogram.cpp", "ext/opencv/cvmatnd.h", "ext/opencv/cvtermcriteria.h", "ext/opencv/iplconvkernel.cpp", "ext/opencv/window.h", "ext/opencv/trackbar.h", "ext/opencv/cvpoint2d32f.cpp", "ext/opencv/cvcapture.h", "ext/opencv/cvmat.h", "ext/opencv/cvsize.h", "images/face_detect_from_lena.jpg", "images/CvMat_sobel.png", "images/CvMat_sub_rect.png", "images/CvSeq_relationmap.png", "setup/setup.mingw.rb", "setup/setup.mswin32.rb", "setup/setup.cygwin.rb", "test/test_cvline.rb", "test/test_cvchain.rb", "test/test_cvseq.rb", "test/test_iplconvkernel.rb", "test/test_cvfont.rb", "test/test_cvmoments.rb", "test/test_cvvideowriter.rb", "test/test_cvpoint2d32f.rb", "test/test_cvsize2d32f.rb", "test/runner.rb", "test/test_cvsurfparams.rb", "test/test_cvbox2d.rb", "test/test_mouseevent.rb", "test/test_curve.rb", "test/helper.rb", "test/test_window.rb", "test/test_cvpoint.rb", "test/test_preliminary.rb", "test/test_cvhaarclassifiercascade.rb", "test/test_cvsurfpoint.rb", "test/test_cvpoint3d32f.rb", "test/test_cvtwopoints.rb", "test/test_cvmat_dxt.rb", "test/test_iplimage.rb", "test/samples", "test/samples/fruits.jpg", "test/samples/messy0.jpg", "test/samples/baboon.jpg", "test/samples/lines.jpg", "test/samples/partially_blank1.jpg", "test/samples/lena.jpg", "test/samples/str-cv-rotated.jpg", "test/samples/smooth0.jpg", "test/samples/blank0.jpg", "test/samples/lena-256x256.jpg", "test/samples/airplane.jpg", "test/samples/blank5.jpg", "test/samples/contours.jpg", "test/samples/baboon200_rotated.jpg", "test/samples/one_way_train_0000.jpg", "test/samples/lena-32x32.jpg", "test/samples/lena-eyes.jpg", "test/samples/smooth4.jpg", "test/samples/blank9.jpg", "test/samples/blank1.jpg", "test/samples/blank8.jpg", "test/samples/str-ov.jpg", "test/samples/smooth2.jpg", "test/samples/cat.jpg", "test/samples/stuff.jpg", "test/samples/str-cv.jpg", "test/samples/blank3.jpg", "test/samples/baboon200.jpg", "test/samples/blank2.jpg", "test/samples/smooth1.jpg", "test/samples/partially_blank0.jpg", "test/samples/movie_sample.avi", "test/samples/messy1.jpg", "test/samples/inpaint-mask.bmp", "test/samples/smooth6.jpg", "test/samples/lena-inpaint.jpg", "test/samples/blank6.jpg", "test/samples/blank4.jpg", "test/samples/smooth3.jpg", "test/samples/blank7.jpg", "test/samples/one_way_train_0001.jpg", "test/samples/smooth5.jpg", "test/samples/haarcascade_frontalface_alt.xml.gz", "test/test_cvsize.rb", "test/test_cvcontour.rb", "test/test_cvcircle32f.rb", "test/test_cvmat_drawing.rb", "test/test_cvrect.rb", "test/test_trackbar.rb", "test/test_cvtermcriteria.rb", "test/test_opencv.rb", "test/test_cvcapture.rb", "test/test_cvmat.rb", "test/test_cvhumoments.rb", "test/test_cvscalar.rb", "test/test_cvconnectedcomp.rb", "test/test_cvavgcomp.rb", "test/test_cvmat_imageprocessing.rb", "test/test_cvslice.rb"]

  s.homepage = %q{http://blueruby.mydns.jp/opencv}
  s.rdoc_options = ["--main", "README.rdoc"]
  s.require_paths = ["lib"]
  s.rubyforge_project = %q{opencv}
  s.rubygems_version = %q{1.6.2}
  s.summary = %q{OpenCV wrapper for Ruby.}
  s.test_files = ["test/test_cvmoments.rb", "test/test_cvhumoments.rb", "test/test_cvmat_drawing.rb", "test/test_iplconvkernel.rb", "test/test_cvconnectedcomp.rb", "test/test_cvscalar.rb", "test/test_cvline.rb", "test/test_cvcircle32f.rb", "test/test_cvchain.rb", "test/test_opencv.rb", "test/test_cvrect.rb", "test/test_cvfont.rb", "test/test_cvpoint2d32f.rb", "test/test_cvtermcriteria.rb", "test/test_cvmat_imageprocessing.rb", "test/test_cvpoint.rb", "test/test_cvbox2d.rb", "test/test_cvcontour.rb", "test/test_cvmat_dxt.rb", "test/test_preliminary.rb", "test/test_cvsize.rb", "test/test_cvsize2d32f.rb", "test/test_iplimage.rb", "test/test_cvtwopoints.rb", "test/test_cvseq.rb", "test/test_cvpoint3d32f.rb", "test/test_cvmat.rb"]

  if s.respond_to? :specification_version then
    s.specification_version = 3

    if Gem::Version.new(Gem::VERSION) >= Gem::Version.new('1.2.0') then
      s.add_development_dependency(%q<rake-compiler>, [">= 0"])
      s.add_development_dependency(%q<hoe-gemspec>, [">= 0"])
      s.add_development_dependency(%q<rspec>, [">= 0"])
      s.add_development_dependency(%q<hoe>, [">= 2.9.4"])
    else
      s.add_dependency(%q<rake-compiler>, [">= 0"])
      s.add_dependency(%q<hoe-gemspec>, [">= 0"])
      s.add_dependency(%q<rspec>, [">= 0"])
      s.add_dependency(%q<hoe>, [">= 2.9.4"])
    end
  else
    s.add_dependency(%q<rake-compiler>, [">= 0"])
    s.add_dependency(%q<hoe-gemspec>, [">= 0"])
    s.add_dependency(%q<rspec>, [">= 0"])
    s.add_dependency(%q<hoe>, [">= 2.9.4"])
  end
end
