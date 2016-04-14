import java.util.Arrays;
public class mergesort {
	int B[];
	int size;
	int num_comparision = 0;
	public mergesort (int A[], int array_size)
	{
		B = new int[array_size];
		this.size = array_size;
		for(int i =0; i<array_size; i++) B[i] = A[i];
		mergeSort(B);
	}
	public void mergeSort(int[] A) 
	{
		if (A.length > 1) {
            int q = A.length/2;

            int[] leftArray = Arrays.copyOfRange(A, 0, q);
            int[] rightArray = Arrays.copyOfRange(A,q,A.length);

            mergeSort(leftArray);
            mergeSort(rightArray);

            merge(A,leftArray,rightArray);
        }
    }

    public void merge(int[] a, int[] l, int[] r) 
    {
        int totElem = l.length + r.length;
        int i,li,ri;
        i = li = ri = 0;
        while ( i < totElem) 
        {
            if ((li < l.length) && (ri<r.length)) 
            {
            	this.num_comparision++;
                if (l[li] < r[ri]) 
                {
                    a[i] = l[li];
                    i++;
                    li++;
                }
                else 
                {
                    a[i] = r[ri];
                    i++;
                    ri++;
                }
            }
            else 
            {
                if (li >= l.length) 
                {
                    while (ri < r.length) 
                    {
                        a[i] = r[ri];
                        i++;
                        ri++;
                    }
                }
                if (ri >= r.length) 
                {
                    while (li < l.length) 
                    {
                        a[i] = l[li];
                        li++;
                        i++;
                    }
                }
            }
        }
    }
}
