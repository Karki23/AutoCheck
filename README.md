# AutoCheck
Done as a course project in Advanced Algorithms.

It uses weighted edit distance as a parameter for spell checking. 
The weight depends upon the key distances (based on the standard keyboard layout) when a replacement needs to be done between two characters.
Auto correct is done by finding words in a dictionary that has a edit distance below a certain threshold from the wrong word.
It uses the Burkhard Keller (BK Tree) tree to do so.
