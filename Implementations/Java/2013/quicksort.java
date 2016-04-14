public class quicksort {
	int B[];
	int size;
	int num_comparison = 0;
	int pivot = 0;
	public quicksort (int A[], int array_size, int pivot_policy)
	{
		B = new int[array_size];
		this.size = array_size;
		this.pivot = pivot_policy;
		for(int i =0; i<array_size; i++) B[i] = A[i];
		quickSort(B, 0, array_size-1);
	}
	public void quickSort(int A[], int start, int end)
	{
		if(start > end) return;
 		if(end-start<=4)
		{
		    smallsort s = new smallsort(A, start, end);
		    num_comparison = num_comparison + s.num_comparison;
		    s = null;
		    return;
		}

		
		pivot new_pivot = new pivot (A, start, end, this.pivot);
		num_comparison = num_comparison + new_pivot.num_comparison;
		
		
		int pivot_pos = new_pivot.pivot_index;
		
		//In median of medians, array is already partitioned.
		if(pivot !=3)	pivot_pos = partition(A, start, end, new_pivot.pivot_index);
		
		quickSort(A, start, pivot_pos-1);
		quickSort(A, pivot_pos+1, end);
		new_pivot = null;


	}
	public int partition(int A[], int start, int end, int pivot_index)
	{
		int pivot_value = A[pivot_index];
		swap(A, pivot_index, end);
		int storeIndex = start;
		
		for(int i=start; i<end; i++)
		{
			num_comparison++;
			if(A[i] < pivot_value)
			{
				swap(A, storeIndex, i);
				storeIndex++;
			}
		}
		swap(A, end, storeIndex);
		return storeIndex;
		
	}
	public void swap(int A[], int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
}
