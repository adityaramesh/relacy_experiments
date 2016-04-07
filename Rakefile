require 'rake/clean'

cxx = ENV['CLANGPLUSPLUS']

langflags = "-std=c++1z"
wflags    = "-Wall -Wextra -pedantic -Wno-dollar-in-identifier-extension"
archflags = "-march=native"
incflags  = "-I . -isystem relacy"
ldflags   = "-lpthread"

if cxx.include? "clang"
	optflags = "-Ofast -fno-fast-math -flto"
elsif cxx.include? "g++"
	optflags = "-Ofast -fno-fast-math -flto"
end

cxxflags = "#{langflags} #{wflags} #{archflags} #{incflags} #{optflags}"

dirs = ["out"]
examples = FileList["examples/*.cpp"].map{|f| [f, f.sub("examples", "out").ext("run")]}

multitask :default => examples.map{|src, out| out}

dirs.each do |d|
	directory d
end

examples.each do |src, out|
	file out => [src] + dirs do
		sh "#{cxx} #{cxxflags} -o #{out} #{src} #{ldflags}"
	end
end

task :clobber => dirs do
	FileList["out/*.run"].each{|f| File.delete(f)}
end
