# DistinctKPairedSums
Every k number sums to a different number, the algorithm finds the set that maximizes the total of its elements which obey the distinct k sums rule. 

For example, for k = 2

70  69  68  66  62  55  46  41  36  24  6 
and the total is 543. 

The algorithm starts by finding an initial solution. 
For max = 70, it finds:


70 69 68 66 63 58 50 41 32 18
and its total is 535

Then, in findMaxResult function, 

it starts with last array element up to third to start modifying such as:

70 69 68 66 63 58 50 41 32 
and look for 17, 16, 15, 14.... and finds new array that obeys the rule. 

Then, 
70 69 68 66 63 58 50 41
and look for 31, 30, 29, 28... and finds new arrays that obeys the k sum rule.

Finally, 
70 69 68 
and look for 65, 64, 63...  and finds new arrays that obeys the k sum rule

and all the stages above are run recursively. 

The algorithm finally finds the array above that sums to 543


