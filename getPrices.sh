#!/bin/bash
#=============================================================================#
#               ________  _______  _________                                  #
#              |\   ____\|\  ___ \|\___   ___\                                #
#              \ \  \___|\ \   __/\|___ \  \_|                                #
#               \ \  \  __\ \  \_|/__  \ \  \                                 #
#                \ \  \|\  \ \  \_|\ \  \ \  \                                #
#                 \ \_______\ \_______\  \ \__\                               #
#                  \|_______|\|_______|   \|__|                               #
#      ________  ________  ___  ________  _______   ________                  #
#     |\   __  \|\   __  \|\  \|\   ____\|\  ___ \ |\   ____\                 #
#     \ \  \|\  \ \  \|\  \ \  \ \  \___|\ \   __/|\ \  \___|_                #
#      \ \   ____\ \   _  _\ \  \ \  \    \ \  \_|/_\ \_____  \               #
#       \ \  \___|\ \  \\  \\ \  \ \  \____\ \  \_|\ \|____|\  \              #
#        \ \__\    \ \__\\ _\\ \__\ \_______\ \_______\____\_\  \             #
#         \|__|     \|__|\|__|\|__|\|_______|\|_______|\_________\            #
#                                                     \|_________|            #
#             ___  ________   ________  _________  ________  ________         #
#            |\  \|\   ___  \|\   __  \|\___   ___\\   __  \|\   __  \        #
#            \ \  \ \  \\ \  \ \  \|\  \|___ \  \_\ \  \|\  \ \  \|\  \       #
#             \ \  \ \  \\ \  \ \   __  \   \ \  \ \ \  \\\  \ \   _  _\      #
#              \ \  \ \  \\ \  \ \  \ \  \   \ \  \ \ \  \\\  \ \  \\  \|     #
#               \ \__\ \__\\ \__\ \__\ \__\   \ \__\ \ \_______\ \__\\ _\     #
#                \|__|\|__| \|__|\|__|\|__|    \|__|  \|_______|\|__|\|__|    #
#                                                                             #
#title           :getPrices                                                   #
#description     :This script will download the prices files on a Linux O.S.  #
#authors         :Dimitri Thomopulos, Gabriele Iommazzo                       #
#date            :20180730                                                    #
#version         :1.00                                                        #
#usage           :Just exegute it (./getPrices)                               #
#notes           :Remember to make it executable (run the command             #
#                 "sudo chmod +x RUN")                                        #
#bash_version    :                                                            #
#=============================================================================#

INFDIR="Prices";

if [ $1 = "-h" ] || [ $1 = "--help" ]; then
	echo '';
	echo 'This is a script to download prices data files in Excel format';
	echo 'from http://www.mercatoelettrico.org/';
	echo 'The files are stored in the folder "Prices"';
	echo '';
	echo 'Usage: ./getPrices.sh [OPTION]';
	echo '';
	echo 'Possible options';
	echo '  -h, --help     display this help and exit';
	echo '  -v, --version  output version information and exit';
	echo '';
	echo 'Report getPrices bugs to thomopulos[at]lix[dot]polytechnique[dot]fr';
else
	if [ $1 = "-v" ] || [ $1 = "--version" ]; then
		echo '';
		echo 'getPrices v.0.99';
		echo 'This is free software: you are free to change and redistribute it.'
		echo 'There is NO WARRANTY, to the extent permitted by law.'
		echo '';
		echo 'Written by Gabriele Iommazzo and Dimitri Thomopulos.';
	else
		if [ $1 = "--like" ] && [ $2 = "crazy" ]; then
			echo '       __.__'
			echo '   .-'\''"  .  "'\''-.'
			echo ' .'\''  / . '\'' . \  '\''.'
			echo '/_.-..-..-..-..-._\ "Could Be Worse. Could Be Raining."'
			echo '         #                              Igor, in Young Frankenstein'
			echo '         #'
			echo '         #'
			echo '         #'
			echo '         #'
			echo '    .^._.#.  D.T.'
			echo '     '\''"-"'\'''
			echo '';
		else
			mkdir -p $INFDIR;

			for number in {4..9}
				do wget "http://www.mercatoelettrico.org/En/MenuBiblioteca/Documenti/Anno200$number.zip"
			done

			for number in {10..12}
				do wget "http://www.mercatoelettrico.org/En/MenuBiblioteca/Documenti/Anno20$number.zip";
			done

			if ! command -v unzip &> /dev/null; then
				echo 'The command "unzip" could not be found'
				echo "Please, extract every .zip file in folder Prices"
			else
				for x in *.zip
					do unzip -o "$x" -d $INFDIR
				done

				rm *zip*

				mv $INFDIR/Anno2004.xls $INFDIR/"Anno 2004".xls
			fi
		fi
	fi
fi

exit 0
