Victoria Fabrizio
vfabriz1
B00579949
I did not do the extra credit

My file code runs in about 12 seconds for the short trace and about 2 minutes for the long trace.

The only problem I encounter is that my output is exactly the same as the correct_outputs files except diff says that the whitespace at the end of the line is wrong.
However when I check myself, it is the same.
If you run it with diff -Z correct_outputs/filename.txt output.txt it will be right because it ignores the end space.