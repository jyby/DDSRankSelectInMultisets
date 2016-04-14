/*Kaligosi et. al's Offline multiselection algorithm (B+o(B)+O(n))
 * The query q finds A[q] in array, does not find A[start+q]
 */
import java.util.*;
public class Kaligosi {
	int l;	//run_length
	int B[];
	int query[];
	int answer[];
	int num_comparison = 0;
	int pivot = 0;
	
	//supplement array for mark start of runs (1: new runs start)
	ArrayList<runs> W;
	
	
	public Kaligosi(int A[], int array_size, int pivot_type)
	{
		this.l = 1;
		this.pivot = pivot_type;
		B = new int[array_size];
		W = new ArrayList<runs>();
		
		for(int i=0; i<array_size; i++) 
		{
			B[i] = A[i];
			W.add(new runs(i, 1));
		}

	}
	public int[] select (int q[], int query_size, double entropy)
	{
		//set l
		if(l < (Math.log(entropy/(double)B.length)/Math.log(2)))
		{
			l = (int)(Math.log(entropy/(double)B.length)/Math.log(2))+1;
		}
		
		query = new int[query_size];
		answer = new int[query_size];
		for(int i = 0; i<query_size; i++)
		{
			query[i] = q[i];
			answer[i] = -1;
		}
		
		do_select(B, query, W, 0, W.size());
		//for check
		/*for(int i=0 ; i<q.length; i++) System.out.print(q[i]+" ");
		System.out.println("");
		for(int i=0 ; i<answer.length; i++) System.out.print(answer[i]+" ");
		System.out.println("");
		*/
		return answer;
	}
	public void do_select(int B[], int query[], ArrayList<runs> W, int answer_start, int num_runs)
	{
		quickselect	qselect = new quickselect(pivot);
		//System.out.println("l = " + l );
		/*System.out.println("query");
		for(int i=0; i<query.length; i++) System.out.print(query[i]+ " ");
		System.out.println("");
		*/
		
		//if array size <= 5 do small sort
		if(B.length <=5)
		{
			smallsort s = new smallsort(B, 0, B.length-1);
			for(int i=0; i<query.length; i++)
			{
				answer[answer_start+i] = B[query[i]];
			}
			num_comparison = num_comparison + s.num_comparison;
			return;
		}
		
		//Do merge sort if array size is less than 4l^2
		if(B.length < 4*l*l)
		{
			mergesort m = new mergesort(B, B.length);
			for(int i = 0; i<B.length; i++) B[i] = m.B[i];
			
			for(int i=0; i<query.length; i++)
			{
				//System.out.println("answer" + query[i] + " "+ B[query[i]]);
				answer[answer_start+i] = B[query[i]];
			}
			num_comparison = num_comparison + m.num_comparision;
			return;
		}
		
		//Merge runs until at most one run < l
		int check = 0;
		while(true)
		{
			check = 0;
			int position1 = -1;
			int position2 = -1;
			for(int i = 0; i<W.size(); i++)
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
					i--;
				}
				
			}
			if(check < 2) break;
		}
		
		W.trimToSize();
		//check
		/*for (runs run : W) 
		{
		     System.out.println("start = " + run.start_position + "length" + run.length);
		     for(int i = run.start_position; i<run.start_position+run.length; i++) System.out.print(B[i]+ " ");
		     System.out.println("");
		}*/

		//create median array and store medians of each runs
		int median_array[] = new int[W.size()];
		for(int i = 0; i<W.size(); i++)
		{
			median_array[i] = B[W.get(i).start_position+W.get(i).length/2];
		}
		
		//find median of medians in median array.
		int pos = median_array.length/2 - 1;
		if(pos < 0) pos = 0;
		
		//System.out.println("num com before med " + num_comparison);
		int median_value = qselect.qselect(median_array, 0, median_array.length-1, pos);
		//System.out.println("median " +median_value);
		num_comparison = num_comparison + qselect.num_comparison;
		//System.out.println("num com after med " + num_comparison);
		
		//split array, runs, query into <=median value and > median value
		ArrayList<Integer> B1 = new ArrayList<Integer>();
		ArrayList<Integer> B2 = new ArrayList<Integer>();
		ArrayList<Integer> q1 = new ArrayList<Integer>();
		ArrayList<Integer> q2 = new ArrayList<Integer>();
		ArrayList<runs> r1 = new ArrayList<runs>();
		ArrayList<runs> r2 = new ArrayList<runs>();
		
		
		for (runs run : W) 
		{
			int start = run.start_position;
			int end = run.start_position+run.length-1;
			int mid = (start+end)/2;
			int mark = 0;
			while(start<=end)
			{
				num_comparison++;
				if(B[mid] > median_value) end = mid-1;
				if(B[mid] < median_value) start = mid+1;
				if(B[mid] == median_value)
				{
					start = mid;
					end = mid;
					mark = 1;
					break;
				}
				mid = (start+end)/2;
				
			}
			
			if(mark == 0 && start > run.start_position+run.length-1) mid = run.start_position+run.length-1;
			if(mark == 0 && end < run.start_position) mid = run.start_position-1;
			
			start = run.start_position;
			end = run.start_position+run.length-1;
			//if(B[mid] > median_value) mid--;
			//if(B[end] < median_value) mid = end;
			int old_b1 = B1.size();
			int old_b2 = B2.size();
			for(int i = start; i<=end; i++)
			{
				if(i <= mid) B1.add(B[i]);
				else B2.add(B[i]);
			}
			runs left_run = new runs(old_b1, B1.size()-old_b1);
			runs right_run = new runs(old_b2, B2.size()-old_b2);
			
			if(B1.size()-old_b1 > 0) r1.add(left_run);
			if(B2.size()-old_b2 > 0) r2.add(right_run);
		}
		int new_answer = answer_start;
		for(int i = 0; i<query.length; i++)
		{
			if(query[i] < B1.size())
			{
				q1.add(query[i]);
				new_answer++;
			}
			else q2.add(query[i]-B1.size());
		}
		
		//do recursively
		int array_b1[] = new int[B1.size()];
		int array_b2[] = new int[B2.size()];
		int array_q1[] = new int[q1.size()];
		int array_q2[] = new int[q2.size()];
		//if(i < 10) System.out.print(+array_b1[i]+" ");
		//System.out.println("");
		for(int i = 0; i<B1.size(); i++) array_b1[i] = B1.get(i);
		for(int i = 0; i<B2.size(); i++) array_b2[i] = B2.get(i);
		for(int i = 0; i<q1.size(); i++) array_q1[i] = q1.get(i);
		for(int i = 0; i<q2.size(); i++) array_q2[i] = q2.get(i);
		
		B1 = null;
		B2 = null;
		q1 = null;
		q2 = null;
		median_array = null;
		//System.out.println("b1 size " + array_b1.length + "b2 size " + array_b2.length);
		if(array_q1.length > 0) do_select(array_b1, array_q1, r1, answer_start, r1.size());
		if(array_q2.length > 0) do_select(array_b2, array_q2, r2, new_answer, r2.size());
	}
	
}
