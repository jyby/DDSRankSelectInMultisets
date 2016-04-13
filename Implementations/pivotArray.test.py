import unittest, doctest, copy
from logSort import logSort
from  pivotArray import PartiallySortedArray, maxBubblePass, minBubblePass, preorder

class PartiallySortedArrayTest(unittest.TestCase):
    """Basic tests for algorithms computing prefix free codes.
    """
        
    def testMaxBubblePassOnSortedArray(self):
        """Test Max bubble pass on sorted array.
        """
        W = [1,2,3,4,5,6,7,8]
        T = PartiallySortedArray(W)
        T.pivot = [1]*len(T.values)
        T.maxBubblePass()
        self.assertEqual(T.values,W)
        self.assertEqual(T.pivot,[1,1,1,1,1,1,1,1])
 
    def testMaxBubblePassOnInvertedArray(self):
        """Test Max bubble pass on inverted array.
        """
        W = [8,7,6,5,4,3,2,1]
        T = PartiallySortedArray(W)
        T.pivot = [1]*len(T.values)
        T.maxBubblePass()
        self.assertEqual(T.values,[7,6,5,4,3,2,1,8])
        self.assertEqual(T.pivot,[0,0,0,0,0,0,0,1])

    def testMaxBubblePassOnShuffledArray(self):
        """Test Max bubble pass on Shuffled array.
        """
        T = PartiallySortedArray([4,3,2,1,5,8,7,6])
        T.pivot = [1]*len(T.values) # Testing max Bubble Pass form pivots set to 1.
        T.maxBubblePass()
        self.assertEqual(T.values,[3,2,1,4,5,7,6,8])
        self.assertEqual(T.pivot,[0,0,0,1,1,0,0,1])

    def testMinBubblePassOnSortedArray(self):
        """Test min bubble pass on sorted array.
        """
        W = [1,2,3,4,5,6,7,8]
        T = PartiallySortedArray(W)
        T.pivot = [1]*len(T.values) # Testing min buble pass from pivots set to 1
        T.minBubblePass()
        self.assertEqual(T.values,W)
        self.assertEqual(T.pivot,[1,1,1,1,1,1,1,1])

    def testMinBubblePassOnInvertedArray(self):
        """Test min bubble pass on inverted array.
        """
        W = [8,7,6,5,4,3,2,1]
        T = PartiallySortedArray(W)
        T.pivot = [1]*len(T.values)  # Testing min buble pass from pivots set to 1
        T.minBubblePass()
        self.assertEqual(T.values,[1,8,7,6,5,4,3,2])
        self.assertEqual(T.pivot,[1,0,0,0,0,0,0,0])

    def testMinBubblePassOnShuffledArray(self):
        """Test min bubble pass on Shuffled array.
        """
        T = PartiallySortedArray([4,3,2,1,5,8,7,6])
        T.pivot = [1]*len(T.values) # Testing min buble pass from pivots set to 1
        T.minBubblePass()
        self.assertEqual(T.values,[1,4,3,2,5,6,8,7])
        self.assertEqual(T.pivot,[1,0,0,0,1,1,0,0])

    def testPreorderOnSmallShuffledArray(self):
        """Test preorder pass on a small Shuffled array with one point already in place.
        """
        T = PartiallySortedArray([4,3,2,1,5,8,7,6])
        T.preorder()
        self.assertEqual(T.values,[1,2,3,4,5,6,7,8])
        self.assertEqual(T.pivot,[1, 1, 1, 1, 1, 1, 1, 1])

    def testPreorderOnLargeInvertedArray(self):
        """Test preorder pass on a large inverted array.
        """
        T = PartiallySortedArray([ 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1])
        T.preorder()
        self.assertEqual(T.values,[1, 2, 3, 4, 5, 6, 7, 8, 9, 14, 13, 12, 11, 10, 15])
        self.assertEqual(T.pivot,[1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1])

    def testPreorderOnTwoInvertedArraysConcatenated(self):
        """Test preorder pass on two inverted arrays concatenated.
        """
        T = PartiallySortedArray([ 7, 6, 5, 4, 3, 2, 1, 8, 15, 14, 13, 12, 11, 10, 9])
        T.preorder()
        self.assertEqual(T.values,[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 13, 12, 11, 15])
        self.assertEqual(T.pivot,[1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1])

    def testUpdatePartialSum(self):
        W = [1]*8
        A = PartiallySortedArray(W)
        A.updatePartialSum(0,len(W))
        self.assertEqual(A.partialSums,[1,2,3,4,5,6,7,8])
        
    def testRangeSum(self):
        W = [1]*8
        A = PartiallySortedArray(W)
        self.assertEqual(A.rangeSum(1,4),3)

    def testPartialSumOnOrderedArray(self):
        W = [1]*8
        A = PartiallySortedArray(W)
        self.assertEqual(A.partialSum(1),1)

    # def testPartialSumOnDisorderedArray(self):
    #     W = [9,8,7,6,5,4,3,2,1]
    #     A = PartiallySortedArray(W)
    #     self.assertEqual(A.partialSum(2),3)
    #     print A.partialSums
    #     # self.assertEqual(A.rangeSum(4,5),9)

    # def testSelectOnFirstValue(self):
    #     T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
    #     self.assertEqual(T.select(0),1)
    #     self.assertEqual(T.values,[1,70,60,50,40,30,30,30,20,10])
    #     self.assertEqual(T.pivot,[0]*9+[1])

    # def testSelectOnLastValue(self):
    #     T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
    #     self.assertEqual(T.select(9),70)
    #     self.assertEqual(T.values,[60,50,40,30,30,30,20,10,1,70])
    #     self.assertEqual(T.pivot,[0]*9+[1])

    # def testSelectOnLargeNumbersOnRepeatedCentralValue(self):
    #     T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
    #     self.assertEqual(T.select(4),30)
    #     self.assertEqual(T.values,[20, 10, 1, 30, 30, 30, 70, 60, 50, 40])
    #     self.assertEqual(T.pivot,[0,  0, 0,  1,  1,  1,  0,  0,  0,  0])

    # def testSelectOnSmallNumbers(self):
    #     W = [9,8,7,6,5,4,3,2,1,0]
    #     A = PartiallySortedArray(W)
    #     self.assertEqual(A.select(0),0)
    #     self.assertEqual(A.values,[0,9,8,7,6,5,4,3,2,1])

    def testRankOnLastElement(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.rank(60),9)
        self.assertEqual(T.values,[60,50,40,30,30,30,20,10,1,70])

    def testRankOnFirstElement(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.rank(1),0)
        self.assertEqual(T.values,[1,70,60,50,40,30,30,30,20,10])

    def testRankOnMiddle(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.rank(30),3)
        self.assertEqual(T.values,[20, 10, 1, 30, 30, 30, 70, 60, 50, 40])
        self.assertEqual(T.pivot,[0,  0, 0,  1,  1,  1,  0,  0,  0,  0])

    def testFindLeftAndRightPivots(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        T.values = [10,1,20,40,30,30,30,50,70,60]
        T.pivot  = [0, 0, 1, 0, 0, 0, 0, 1, 0, 0]
        self.assertEqual(T.findLeftAndRightPivots(5),(2,7))
        
    def testPartitionByValueOnLastValue(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.PartitionByValue(70),([60,50,40,30,30,30,20,10,1],[70],[]))

    def testPartitionByValueOnFirstValue(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.PartitionByValue(1),([],[1],[70,60,50,40,30,30,30,20,10]))

    def testPartitionByValueOnMiddleValue(self):
        T = PartiallySortedArray([70,60,50,40,30,30,30,20,10,1])
        self.assertEqual(T.PartitionByValue(30),([20, 10, 1], [30, 30, 30], [70, 60, 50, 40]))
        
    def testInitialize(self):
        W = [1,2,3,4,5,6,7,8]
        T = PartiallySortedArray(W)
        self.assertEqual(T.values,W)

        
def main():
    unittest.main()
if __name__ == '__main__':
    doctest.testmod()
    main()
