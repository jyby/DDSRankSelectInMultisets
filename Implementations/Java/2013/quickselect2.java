/*
 * second quick selection algorithm
 * It works same as original quickselect. 
 * Only difference is updating pivot depth and supplement vector for online multiselection. 
 */
public class quickselect2 {
	int pivot_type = 0;
	int num_comparison = 0;
	public quickselect2(int pivot_policy)
	{
		this.pivot_type = pivot_policy;
	}
	//find A[start+k] position
	public int qselect(int A[], int start, int end, int k, int depth[], int depth_start, int vector[])
	{
		//System.out.println("start= " + start+ " end: " + end);
		
		if(start >= end) return A[start];
		
		//if array_size <=5 sort
		if(end-start+1 <=5)
		{
			smallsort s = new smallsort(A, start, end);
			num_comparison = num_comparison + s.num_comparison;
			return A[start+k];
		}
		
		pivot p = new pivot(A, start, end, pivot_type);
		num_comparison = num_comparison + p.num_comparison;
		int position = p.pivot_index;
		if(pivot_type != 3) position = partition(A, start, end, p.pivot_index);
		int pivotDist  = position-start;
		
		depth[position] = depth_start+1;
		vector[position] = 1;
		
		/*System.out.println("pivotk= " + pivotDist+ " K: " + k);
		
		for(int i = start; i<=end; i++) System.out.print(A[i]+" ");
        System.out.println("");
		*/
		
		if (pivotDist == k) return A[position];
		else if( k < pivotDist)	return qselect(A, start, position-1, k, depth, depth_start+1, vector);
		else return qselect(A, position+1, end, k - pivotDist-1, depth, depth_start+1, vector);            

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
