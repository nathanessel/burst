# burst

burst

burst -- Splits an inputted file into multiple files. ====

SYNOPSIS
burst [OPTION] filename

DESCRIPTION
burst is a program that splits a file into multiple files. By default, the original file is split into multiple smaller files by breaking them into 500 lines each.

-m Splits the original file by this specified amount

EXAMPLES
To split a file into multiple files by the default 500 line:

$ burst data.txt
To split a file by a specified amount (ex. 100 lines):

$ burst -m100 data.txt'
$ ls

data.txt data1.txt data2.txt

$ `wc` --lines data1.txt

100   
2016-05-11
