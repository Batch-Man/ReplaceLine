# ReplaceLine
**Description:**
Replace a Line in a Text File.

AUTHOR:	**Kvc & Anic17**

# USAGE

<code>Call ReplaceLine [File] [LineNumber] [NewLineContent]</code>

​	Examples: 		ReplaceLine "Demo.txt" 5 "This is replaced Line."

There are 2 MODES to GET the results...
 MODE 1:	GO INSIDE THE FILE, AND EDIT THAT LINE...
 MODE 2:	REPLACE THAT LINE INSIDE THE FILE...

SYNTAX:


ReplaceLine will automatically, select the MODE whichever is faster for your
Given conditions

INFO ABOUT THE MODES: [GET MAX OUT OF THIS UTILITIY]
MODE 1 is much faster than MODE 2, as in MODE 2 - we create a new separate file
and add the modified line to it at right place and then overwrite existing file
(that is why, REPLACE LINE...)

AND

in MODE 1 - we are going to that line and changing its content and exiting, no
recreation of the entire file with 99% unchanged rows
But, to invoke MODE 1 - it requires 1 special condition as FOLLOWS:
CONDITION: Make Sure that the New line must have the same length as
of previous line in the file, for compatibility...
and you can check the Older line with 'ReadLine' Utility & extract
its length with 'getlen'.

For Example: Replacing "Kvc" with "abc" will invoke Method 1.

For Example: Replacing "Kvc" with "TheKvc" will invoke Method 2.

	"Notice, the number of characters in both cases."

NOTE:
This utility will always choose the most efficient mode to complete the
required action