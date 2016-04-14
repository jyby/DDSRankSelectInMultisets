/*
 * Optimal online multiselection algorithm (B+o(B)+O(n))
 */
import java.util.*;
public class Optimal_Online {
	int B[];
	int num_comparison = 0;
	int pivot = 0;
	//supplement bit vector
	int vector[];
	//pivot depth array (not for determine l)
	int depth[];
	
	//supplement array for mark start of runs (1: new runs start)
	ArrayList<runs> W;
	
	/*
	 * mode (we will give variant on optimal online algorithm
	 * mode 0 : original optimal online
	 * mode 1 : set initial runs as part of consecutive nondecreasing subsequences 
	 */
	int mode = 0;
	
	public Optimal_Online(int A[], int array_size, int pivot_type, int mode)
	{
		this.pivot = pivot_type;
		B = new int[array_size];
		vector = new int[array_size];
		depth = new int[array_size];
		W = new ArrayList<runs>();
		
		this.mode = mode;
		int start_subseq = 1;
		int subseq_inlength = 0;
		int subseq_delength = 0;
		
		for(int i=0; i<array_size; i++)
		{
			B[i] = A[i];
			vector[i] = 0;
			depth[i] = -1;
			if(mode == 0) W.add(new runs(i, 1));
			else
			{
				if(i == 0)
				{
					W.add(new runs(i, 1));
				}
				if(i > 0 && i<array_size-1)
				{
					num_comparison++;
					if(subseq_inlength == 0) 
					{
						subseq_inlength++;
						subseq_delength++;
					}
					else
					{
						if(B[i] > B[i-1])
						{
							if(subseq_delength > 1 && (mode ==2 || mode ==4))
							{
								int temp_arr[] = new int[subseq_delength];
								for(int j=0; j<temp_arr.length; j++) temp_arr[j] = B[start_subseq+j];
								Collections.reverse(Arrays.asList(temp_arr));
								for(int j=0; j<temp_arr.length; j++) B[start_subseq+j] = temp_arr[j];
								W.add(new runs(start_subseq, subseq_delength));
								
								start_subseq = i;
								subseq_delength = 1;
							}
							else subseq_inlength++;
						}
						else 
						{
							//for(int j = start_subseq ; j<start_subseq+subseq_length; j++) System.out.print(A[j]+" ");
							//System.out.println("");
							if(subseq_inlength > 1 || (mode == 1|| mode ==3))
							{
								W.add(new runs(start_subseq, subseq_inlength));
								start_subseq = i;
								subseq_inlength = 1;
							}
							else 
							{
								subseq_delength++;
							}
						}
						if(i == array_size-2) W.add(new runs(start_subseq, Math.max(subseq_delength, subseq_inlength)));
					}
				}
				if(i == array_size - 1)
				{
					W.add(new runs(i, 1));
				}
			}
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
		int run_start = 0;
		int run_end = 0;
		start = start+1;
		end = end -1;

		for(int i =0; i<W.size(); i++)
		{
			if(W.get(i).start_position+W.get(i).length > start)
			{
				run_start = i;
				break;
			}
		}
		
		for(int i =0; i<W.size(); i++)
		{
			if(W.get(i).start_position+W.get(i).length > end)
			{
				run_end = i;
				break;
			}
		}
		
		return optimal_select(start, end, q-start, W.get(run_start).start_position, W.get(run_end).start_position);
	}
	public int optimal_select(int start, int end, int q, int run_start_position, int run_end_position)
	{
		//find run_start and run_end
		int run_start = 0;
		int run_end = 0;
		for(int i = 0; i<W.size(); i++)
		{
			if(W.get(i).start_position == run_start_position) run_start = i;
			if(W.get(i).start_position == run_end_position) run_end = i;
		}
		//find maximal depth value in this range
		int max_depth = -1;
		for(int i=start-1; i<=end+1; i++)
		{
			if(depth[i] > max_depth) max_depth = depth[i];
		}
		
		//determine l value
		int l =  1+(int)(Math.log((double)max_depth+1)/Math.log(2));
		
		if(mode >2 )
		{
			int longest_run_length = 1;
			for(int i = run_start; i<=run_end; i++)
			{
				if(W.get(i).length > longest_run_length) longest_run_length = W.get(i).length;
			}
			if(l < longest_run_length) l = longest_run_length;
		}
		
		//System.out.println("array start = " + start + " array end = "+ end);
		//System.out.println("l = " + l);
		//System.out.println("run start = " + run_start + " run end = "+ run_end);
		
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
		
		//if array_size less than 4*l*l, sort them and mark vector
		if(end-start+1 < 4*l*l)
		{
			int tempB[] = new int[end-start+1];
			for(int i =0; i<tempB.length; i++) tempB[i] = B[start+i];
			mergesort m = new mergesort(tempB, tempB.length);
			for(int i = 0; i<tempB.length; i++) B[start+i] = m.B[i];
			num_comparison = num_comparison + m.num_comparision;
			for(int i = start ; i<=end; i++)
			{
				vector[i] = 1;
				depth[i] = max_depth+1;
			}
			tempB = null;
			return B[start+q];
		}
		
		//Merge runs until at most one run < l
		int check = 0;
		while(true)
		{
			check = 0;
			int position1 = -1;
			int position2 = -1;
			for(int i = run_start; i<=run_end; i++)
			{
				if(position1 == -1 && W.get(i).length < l) 
				{
					position1 = i;
					continue;
				}
				if(position1 != -1 && position2 == -1 && W.get(i).length < l) position2 = i;
				if(position1 != -1 && position2 != -1)
				{
					//System.out.println(position1 + " " + position2);
					//System.out.println(W.get(position1).start_position + " " + W.get(position1).length + " "+W.get(position2).start_position + " " + W.get(position2).length);
					num_comparison = num_comparison + W.get(i).merge(B, W.get(position1), W.get(position2), W, position1, position2);
					W.remove(position1+1);
					position1 = -1;
					position2 = -1;
					check = 2;
					run_end--;
					i--;
				}
				
			}
			if(check < 2) break;
		}
		
		W.trimToSize();
		//check
		/*for (int j = run_start; j<=run_end ; j++) 
		{
			runs run = W.get(j);
		     System.out.println("start = " + run.start_position + " length" + run.length);
		     for(int i = run.start_position; i<run.start_position+run.length; i++) System.out.print(B[i]+ " ");
		     System.out.println("");
		}*/
		
		quickselect qselect = new quickselect(pivot); 
		
		//create median array and store medians of each runs
		int median_array[] = new int[run_end-run_start+1];
		for(int i = 0; i<run_end-run_start+1; i++)
		{
			median_array[i] = B[W.get(i+run_start).start_position+W.get(i+run_start).length/2];
		}
		
		//find median of medians in median array.
		int pos = median_array.length/2 - 1;
		if(pos < 0) pos = 0;
		//System.out.println("array size " +median_array.length);
		//System.out.println("num com before med " + num_comparison);
		int median_value = qselect.qselect(median_array, 0, median_array.length-1, pos);
		//System.out.println("median " +median_value);
		num_comparison = num_comparison + qselect.num_comparison;
		
		//System.out.println("num com after med " + num_comparison);
		
		
		/*
		 * split array, runs into <median value and > median value and set median value as pivot
		 * and store them into original array and run array
		 */
	
		ArrayList<Integer> B1 = new ArrayList<Integer>();
		ArrayList<Integer> B2 = new ArrayList<Integer>();
		ArrayList<runs> r1 = new ArrayList<runs>();
		ArrayList<runs> r2 = new ArrayList<runs>();
		
		
		for (int j = run_start; j<=run_end ; j++) 
		{
			runs run = W.get(j);
			int first = run.start_position;
			int second = run.start_position+run.length-1;
			int mid = (first+second)/2;
			int mark = 0;
			while(first<=second)
			{
				num_comparison++;
				if(B[mid] > median_value) second = mid-1;
				if(B[mid] < median_value) first = mid+1;
				if(B[mid] == median_value)
				{
					first = mid;
					second = mid;
					mark = 1;
					break;
				}
				mid = (first+second)/2;
				
			}
			
			if(mark == 0 && first > run.start_position+run.length-1) mid = run.start_position+run.length-1;
			if(mark == 0 && second < run.start_position) mid = run.start_position-1;
			
			first = run.start_position;
			second = run.start_position+run.length-1;
			//if(B[mid] > median_value) mid--;
			//if(B[end] < median_value) mid = end;
			int old_b1 = B1.size();
			int old_b2 = B2.size();
			for(int i = first; i<=second; i++)
			{
				if(B[i] != median_value)
				{
					if(i <= mid) B1.add(B[i]);
					else B2.add(B[i]);
				}
			}
			runs left_run = new runs(old_b1, B1.size()-old_b1);
			runs right_run = new runs(old_b2, B2.size()-old_b2);
			
			if(B1.size()-old_b1 > 0) r1.add(left_run);
			if(B2.size()-old_b2 > 0) r2.add(right_run);
		}
		//System.out.println("B1 " +B1.size()+" B2 "+ B2.size()+ " original " + (end-start+1));
		//copy to original array and increase pivot position's pivot depth
		ArrayList<runs> r3 = new ArrayList<runs>();
		int original_runsize = W.size();
		for(int i = run_end+1; i<W.size() ; i++)
		{
			runs temp_run = new runs(W.get(i).start_position, W.get(i).length);
			r3.add(temp_run);
		}
		//System.out.println(" original W length " +W.size() +" start "+run_start);
		//System.out.println(" r3 size " +r3.size());
		
		for(int i = run_start; i<original_runsize; i++)
		{
			W.remove(W.size()-1);
		}
		
		//System.out.println(" after W length " +W.size() +" start "+run_start);
		
		for(int i = 0 ; i<B1.size(); i++)
		{
			B[start+i] = B1.get(i);
		}
		
		for(int i = 0; i<r1.size(); i++)
		{
			//System.out.println("run1 position " +(r1.get(i).start_position+start) +" run1 length "+r1.get(i).length);
			runs temp_run = new runs(r1.get(i).start_position+start, r1.get(i).length);
			W.add(temp_run);
			//System.out.println("W length " +W.size() +" start "+run_start);
		}
		
		B[start+B1.size()] = median_value;
		runs middle_run = new runs(start+B1.size(),0);
		W.add(middle_run);
		depth[start+B1.size()] = max_depth+1;
		vector[start+B1.size()] = 1;
		
		for(int i = 0; i<B2.size(); i++)
		{
			B[start+B1.size()+1+i] = B2.get(i);
		}
		
		for(int i = 0; i<r2.size(); i++)
		{
			//System.out.println("run2 position " +(r2.get(i).start_position+start) +" run2 length "+r2.get(i).length);
			runs temp_run = new runs(r2.get(i).start_position+start+B1.size()+1, r2.get(i).length);
			W.add(temp_run);
		}
		
		for(int i = 0; i<r3.size(); i++)
		{
			W.add(new runs (r3.get(i).start_position, r3.get(i).length));
		}
		
		int position = B1.size();
		int r1_size = r1.size();
		int r2_size = r2.size();
		
		int left_runstart = W.get(run_start).start_position;
		int left_runend = W.get(run_start+r1_size-1).start_position;
		int right_runstart = W.get(run_start+r1_size+1).start_position;
		int right_runend = W.get(run_start+r1_size+r2_size).start_position;
		
		B1 = null;
		B2 = null;
		r1 = null;
		r2 = null;
		r3 = null;
		median_array =null;
		//System.out.println("position " +position+ " query "+ q);
		//do recursively
		
		/*for(int i = run_start; i<=run_start+r1_size-1 ; i++) 
		{
			System.out.println("left start " + W.get(i).start_position + " left length " + W.get(i).length);
		}
		System.out.println("left position start " + start + " left position end " +(start+position-1));
		*/
		//System.out.println("num com " + num_comparison);
		if(q == position) return B[start+q];
		if(q > position) return optimal_select(start+position+1, end, q-(start+position+1), right_runstart , right_runend);
		else return optimal_select(start, start+position-1, q, left_runstart,left_runend );
		
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
