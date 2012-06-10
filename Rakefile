# -*- ruby -*-
require 'rubygems'
require 'hoe'
require './lib/opencv/psyched_yaml'

Hoe.plugin :gemspec

HOE = Hoe.spec 'opencv' do |p|
  p.developer('lsxi', 'masakazu.yonekura@gmail.com')
  p.developer('ser1zw', '')
  p.developer('pcting', 'pcting@gmail.com')
  p.developer('Leszek @zalesz Zalewski', 'contact@zalesz.com')

  p.urls = ['https://github.com/ruby-opencv/ruby-opencv']

  p.need_tar = false
  p.need_zip = false

  p.readme_file  = 'README.rdoc'
  p.history_file = 'CHANGELOG.rdoc'

  p.spec_extras = { :extensions => 'ext/opencv/extconf.rb' }
  p.test_globs = ['test/test_*.rb']

  p.clean_globs << 'lib/*.so' << 'tmp'
  p.extra_dev_deps << ['rake-compiler', '>= 0'] << ['hoe-gemspec'] << ['rspec']
end

require 'rake/extensiontask'

Rake::ExtensionTask.new(HOE.name, HOE.spec) do |ext|
  ext.lib_dir = File.join('lib', 'opencv')
end

HOE.spec.files.delete('.gemtest')
HOE.spec.files.delete('ruby-opencv.gemspec')
HOE.spec.files.delete('opencv.gemspec')
HOE.spec.cert_chain = []
HOE.spec.signing_key = nil

Rake::Task[:test].prerequisites << :compile

# vim: syntax=ruby
