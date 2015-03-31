#!/bin/bash

function processimages {
	dir=$1
	bin_dir=$2
    color_dir=$dir'/bin_color'
    morph_dir=$dir'/bin_morph'
    morph_file=$dir'/feat_morph.csv'
    color_file=$dir'/feat_color.csv'
    eval_morph_file=$dir'/eval_morph.csv'
    eval_color_file=$dir'/eval_color.csv'
    mkdir $color_dir
    mkdir $morph_dir
	./segment $dir $morph_dir $2 morph
	./segment $dir $color_dir $2 color
	./extract $morph_dir $morph_file ext
	./extract $color_dir $color_file ext
    ./evaluate $morph_dir $bin_dir $eval_morph_file 'seg' 'a'
	./evaluate $dir $bin_dir $eval_color_file 'seg' 'a'
    Rscript gen_histograms.R $color_file $color_dir
    Rscript gen_histograms.R $morph_file $morph_dir
}

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/623 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/624 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/625 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/626 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/627 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/628 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/629 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/630 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDcontrole/bin fre

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/755 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/755/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/756 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/756/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/757 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/757/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/758 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/758/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/759 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/759/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/760 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/760/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/761 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/761/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/762 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/762/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/763 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/763/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/764 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDdiabético/764/binario fre

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/060 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/061 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/062 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/063 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDDinsulina/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/623 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/624 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/625 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/626 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEcontrole/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/765 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/765/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/767 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/767/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/768 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/768/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/769 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/769/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/770 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/770/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/771 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/771/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/772 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/772/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/774 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEdiabético/774/binario fre

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/055 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/056 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/057 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/058 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/059 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semDEinsulina/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/619 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/620 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/621 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/622 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDcontrole/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/735 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/735/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/736 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/736/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/737 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/737/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/738 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/738/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/739 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/739/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/740 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/740/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/741 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/741/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/743 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/743/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/744 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDdiabético/744/binario fre

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/050 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/051 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/052 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/053 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/054 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPDinsulina/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/615 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/616 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/617 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/618 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEcontrole/bin

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/745 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/745/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/746 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/746/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/747 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/747/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/748 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/748/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/749 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/749/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/750 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/750/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/751 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/751/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/752 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/752/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/753 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/753/binario fre
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/754 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEdiabético/754/binario fre

processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/045 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/046 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/047 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/048 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/bin
processimages /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/049 /Users/romulobourget/Dropbox/Images/Frenic/original/Frenicos12semPEinsulina/bin