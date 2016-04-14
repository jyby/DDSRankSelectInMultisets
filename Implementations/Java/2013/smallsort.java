//sort small number of elements(at most 5)
public class smallsort {
	int num_comparison = 0;
	public smallsort(int B[], int start, int end)
	{
		int size = end-start+1;
		int A[] = new int[size];
		
		for(int i =0; i<size; i++) A[i] = B[start+i];
		
		if(size == 2)	sort2(A);
		if(size == 3)	sort3(A);
		if(size == 4)	sort4(A);
		if(size == 5)	sort5(A);
		
		for(int i =0; i<size; i++)  B[start+i] = A[i];
		
	}
	public void swap(int A[], int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	public void sort2(int A[])
	{
		num_comparison++;
		if(A[0] > A[1]) swap(A, 0, 1);
	}
	public void sort3(int A[])
	{
		sort2(A);
		num_comparison++;
		if(A[1] > A[2]) swap(A, 1, 2); sort2(A); 
	}
	public void sort4(int A[])
	{
		sort2(A);
		num_comparison++;
		if(A[2] > A[3]) swap(A, 2, 3);
		
		num_comparison++;
		if(A[0] > A[2]) swap(A, 0, 2);
		
		num_comparison++;
		if(A[1] > A[3]) swap(A, 1, 3);
		
		num_comparison++;
		if(A[1] > A[2]) swap(A, 1, 2);
	}
	
	// this one gets 7.5 comps on average (7 is optimal)
	// hopefully with fewer data movements to make it faster
	public void sort5(int A[])
	{
		sort4(A);
		int tmp = A[4];
		for(int i=3; i>=0; i--)
		{
			num_comparison++;
			if(A[i] > tmp) A[i+1] = A[i];
		    else {A[i+1] = tmp; return; }
		}
		A[0] = tmp;
	}
}
