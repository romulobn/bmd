#!/bin/bash

function processimages {
	dir=$1
	color_dir=$dir'/bin_color'
	morph_dir=$dir'/bin_morph'
	morph_file=$dir'/feat_morph.csv'
	color_file=$dir'/feat_color.csv'
	mkdir $color_dir
	mkdir $morph_dir
	./segment $dir $morph_dir $2 morph
	./segment $dir $color_dir $2 color
	./extract $morph_dir $morph_file ext
	./extract $color_dir $color_file ext
}

processimages /Users/romulobourget/Dropbox/Images/Frenic/control/ fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/diabetics/ fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/insulin/ fre


