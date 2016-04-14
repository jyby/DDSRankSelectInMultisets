import java.util.ArrayList;

/*
 * supplement class for represent runs in Kaligosi and Optimal online multiselect algorithm
 * start position represents array's start position. so A[start_position+length] = next run's start position;
 */
public class runs {
	int start_position;
	int length;
	public runs()
	{
		start_position = 0;
		length =1;
	}
	public runs(int start, int length)
	{
		start_position = start;
		this.length = length;
	}
	//merge two runs and return number of comparisons for merge them (merge run1 and run2 to run1)
	public int merge(int A[], runs run1, runs run2, ArrayList<runs> W, int pos1, int pos2)
	{
		int num_comparison = 0;
		int run1_index = 0;
		int run2_index = 0;
		int index = 0;
		int start_position = run1.start_position;
		if(start_position > run2.start_position) start_position = run2.start_position;
		
		/*
		 * change elements between immediately next run of run1 and run2
		 * the start_position(run1)+length of run1 should be run2's start position.
		 */
		
		if(run1.start_position+run1.length != run2.start_position && pos1 < W.size())
		{
			runs run3 = W.get(pos1+1);
			int run3_array[] = new int[run3.length];
			int run2_array[] = new int[run2.length];
			//System.out.println("run3 " + run3.start_position+ " "+ run3.length);
			int temp_array[] = new int[run2.start_position - (run3.start_position + run3.length)];
			int difference = run2.length - run3.length;
			
			
			
			for(int i = 0; i<run3.length; i++) run3_array[i] = A[run3.start_position+i];
			for(int i = 0; i<run2.length; i++) run2_array[i] = A[run2.start_position+i];
			for(int i = 0; i<run2.start_position - (run3.start_position + run3.length) ; i++)
			{
				temp_array[i] = A[run3.start_position+run3.length+i];
			}
			
			int start = run3.start_position;
			
			for(int i = 0; i<run2.length; i++)
			{
				A[start] = run2_array[i];
				start++;
			}
			for(int i = 0; i< temp_array.length ; i++)
			{
				A[start] = temp_array[i];
				start++;
			}
			for(int i = 0; i<run3.length; i++)
			{
				A[start] = run3_array[i];
				start++;
			}
			
			//modify run's information
			W.get(pos1+1).length = run2_array.length;
			for(int i = pos1+2; i<pos2 ; i++)
			{
				W.get(i).start_position = W.get(i).start_position + difference;
			}
			W.get(pos2).length = run3_array.length;
			W.get(pos2).start_position = start - run3_array.length;
		}
		
		int run1_array[] = new int[run1.length];
		int run2_array[] = new int[W.get(pos1+1).length];
		for(int i = 0; i<run1.length; i++) run1_array[i] = A[run1.start_position+i];
		for(int i = 0; i<W.get(pos1+1).length; i++) run2_array[i] = A[W.get(pos1+1).start_position+i];
		
		while(run1_index <run1.length && run2_index < W.get(pos1+1).length)
		{
			num_comparison++;
			if(run1_array[run1_index] < run2_array[run2_index])
			{
				A[start_position+index] = run1_array[run1_index];
				run1_index++;
			}
			else
			{
				A[start_position+index] = run2_array[run2_index];
				run2_index++;
			}
			index++;
		}
		if(run1_index < run1.length)
		{
			for(int i = run1_index; i<run1.length; i++)
			{
				//System.out.println(run1_index+" length " + start_position+index);
				A[start_position+index] = run1_array[run1_index];
				run1_index++;
				index++;
			}
		}
		else
		{
			for(int i = run2_index; i<W.get(pos1+1).length; i++)
			{
				//System.out.println(run1_index+" length "+ start_position+index);
				A[start_position+index] = run2_array[run2_index];
				run2_index++;
				index++;
			}
		}
		
		//modify run1's information
		run1.length = run1.length + W.get(pos1+1).length;
		return num_comparison;
	}
	public void swap(int A[], int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
	
}
