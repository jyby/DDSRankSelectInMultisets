/*
 * Simple Online multiselection algorithm (4B+O(n))
 */
public class Simple_Online {
	int B[];
	int num_comparison = 0;
	int pivot = 0;
	//supplement bit vector
	int vector[];
	//pivot depth array (not used in simple online)
	int depth[];
	public Simple_Online(int A[], int array_size, int pivot_type)
	{
		this.pivot = pivot_type;
		B = new int[array_size];
		vector = new int[array_size];
		depth = new int[array_size];
		for(int i=0; i<array_size; i++)
		{
			B[i] = A[i];
			vector[i] = 0;
			depth[i] = -1;
		}
		//find largest and smallest element
		maxmin();
	}
	//find A[q]
	public int select (int q)
	{
		if(vector[q] == 1) return B[q];
		int start = q;
		int end = q;
		while (vector[start] == 0) start--;
		while (vector[end] == 0) end++;
		return simple_select(start, end, q-start);
	}
	public int simple_select(int start, int end, int q)
	{
		//find maximal depth value in this range (not used)
		int max_depth = -1;
		for(int i=start; i<=end; i++)
		{
			if(depth[i] > max_depth) max_depth = depth[i];
		}
		//if array_size <=5 sort them and mark vector
		if(end-start+1 <=5)
		{
			if(start >=end) return B[start];
			smallsort s = new smallsort(B, start, end);
			num_comparison = num_comparison + s.num_comparison;
			for(int i = start ; i<=end; i++)
			{
				vector[i] = 1;
				depth[i] = max_depth+1;
			}
			return B[start+q];
		}
		//do quickselect on this range
		quickselect2 qselect = new quickselect2(pivot);
		int value = qselect.qselect(B, start, end, q, depth, max_depth, vector);
		num_comparison = num_comparison + qselect.num_comparison;
		return value;
	}
	public void maxmin()
	{
		int small_index = 0;
		int large_index = 0;
		for(int i=0; i<B.length; i++)
		{
			if(B[small_index] > B[i]) small_index = i;
			num_comparison = num_comparison + 1;
		}
		swap(B, 0, small_index);
		
		for(int i=0; i<B.length; i++)
		{
			if(B[large_index] < B[i]) large_index = i;
			num_comparison = num_comparison + 1;
		}
		swap(B, B.length-1, large_index);
		vector[0] = 1;
		vector[B.length-1] = 1;
		depth[0] = 0;
		depth[B.length-1] = 0;
	}
	public void swap(int A[], int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
}
