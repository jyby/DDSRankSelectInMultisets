import unittest, doctest, copy, bisect

class PartiallySortedArray(): 
    """A class receiving an unsorted array, supporting rank and select operators on it in the second most greedy way. 

    """

    def __init__(self,A):
        """Create a Partially Sorted Array supporting rank and select operators from a simple array.

        """
        self.values = sorted(A)
        self.nbRankQueriesProcessed = 0 
        self.nbSelectQueriesProcessed = 0 
            
    def __len__(self):
        """Number of Elements in the Partially Sorted Array.

>>> S = PartiallySortedArray([50,40,30,20,10])
>>> len(S)
5
"""
        return(len(self.values))

    def select(self,r):
        """Element of the set such that r elements are smaller.

>>> S = PartiallySortedArray([50,40,30,20,10])
>>> print(S.select(2))
30
>>> print(S.select(0))
10
"""
        self.nbSelectQueriesProcessed += 1
        return(self.values[r])

    
    def rank(self,x):
        """Number of Elements in the set which are smaller than x.

>>> S = PartiallySortedArray([50,40,30,20,10])
>>> print(S.rank(40))
3
>>> print(S.rank(100))
5
>>> print(S.rank(-10))
0
"""
        self.nbRankQueriesProcessed += 1
        return bisect.bisect_left(self.values, x)

    def rankRight(self,x):
        """Number of Elements in the set which are smaller than or equal to x.

>>> S = PartiallySortedArray([50,40,40,40,40,30,20,10])
>>> print(S.rank(40))
3
>>> print(S.rankRight(40))
7
"""
        self.nbRankQueriesProcessed += 1
        return bisect.bisect_right(self.values, x)

    

    def totalNbOfQueriesPerformed(self):
        """Returns the total number of queries performed on the Partially Sorted Array.


>>> S = PartiallySortedArray([50,40,30,20,10])
>>> print(S.select(2))
30
>>> print(S.nbSelectQueriesProcessed)
1
>>> print(S.totalNbOfQueriesPerformed())
1
>>> print(S.select(0))
10
>>> print(S.totalNbOfQueriesPerformed())
2

"""
        return(self.nbRankQueriesProcessed+self.nbSelectQueriesProcessed)
        
def main():
    unittest.main()
if __name__ == '__main__':
    doctest.testmod()
    main()
    
