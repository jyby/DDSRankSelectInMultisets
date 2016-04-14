/*Dobkin-Munro's Offline multiselection algorithm (3B+O(n))
 * The query q finds A[q] in array, does not find A[start+q]
 */
public class DobkinMunro {
	int B[];
	int query[];
	int answer[];
	int array_size;
	int query_size;
	int num_comparison = 0;
	int pivot = 0;
	public DobkinMunro (int A[], int array_size, int pivot_type)
	{
		this.array_size = array_size;
		this.pivot = pivot_type;
		B = new int[array_size];
		for(int i=0; i<array_size; i++) B[i] = A[i];
	}
	public int[] select (int q[], int query_size)
	{
		this.query_size = query_size;
		query = new int[query_size];
		answer = new int[query_size];
		for(int i = 0; i<query_size; i++)
		{
			query[i] = q[i];
			answer[i] = -1;
		}
		do_select(0, array_size-1, query, 0);
		
		//for check (the query which appears more than twice and revealed when median is found could print only once..)
		/*for(int i=0 ; i<q.length; i++) System.out.print(q[i]+" ");
		System.out.println("");
		for(int i=0 ; i<answer.length; i++) System.out.print(answer[i]+" ");
		System.out.println("");
		*/
		
		return answer;
	}
	public void do_select(int start, int end, int query[], int query_start)
	{
		quickselect	qselect = new quickselect(pivot);
		
		//if array size <= 5 do small sort
		if(end-start+1 <=5)
		{
			smallsort s = new smallsort(B, start, end);
			for(int i=0; i<query.length; i++)
			{
				answer[query_start+i] = B[start+query[i]];
			}
			num_comparison = num_comparison + s.num_comparison;
			return;
		}
		
		//if query size = 1 do simple quickselect
		if(query.length == 1)
		{
			answer[query_start+0] = qselect.qselect(B, start, end, query[0]);
			num_comparison = num_comparison + qselect.num_comparison;
			qselect.num_comparison = 0;
			return;
		}
		
		//find a query element which is closest to (end-start+1)/2-1
		int closest_index = 0;
		int reference = (end-start+1)/2-1;
		
		for(int i =0; i<query.length; i++)
		{
			if(Math.abs(query[closest_index] - reference) > Math.abs(query[i] - reference)) closest_index = i;
		}
		//do quickselect for B[query[closest_index]]
		answer[query_start+closest_index] = qselect.qselect(B, start, end, query[closest_index]);
		
		num_comparison = num_comparison + qselect.num_comparison;
		qselect.num_comparison = 0;
		
		//split query and do recursively
		int small_query_length = 0;
		int large_query_length = 0;
		for(int i = 0; i<query.length; i++)
		{
			if(query[i] < query[closest_index]) small_query_length++;
			if(query[i] > query[closest_index]) large_query_length++;
		}
		int small_query[] = new int[small_query_length];
		int large_query[] = new int[large_query_length];
		int s_index = 0;
		int l_index = 0;
		int last_index = 0;
		int first_index = 0;
		//remove repeated queries
		for (int i=0; i<query.length; i++)
		{
			if(query[i] == query[closest_index]) last_index =i;
		}
		for (int i=0; i<query.length; i++)
		{
			if(query[i] == query[closest_index])
			{
				first_index =i;
				break;
			}
		}
		for(int i=0; i<query.length; i++)
		{
			if(query[i] < query[first_index])
			{
				small_query[s_index] = query[i];
				s_index++;
			}
			if(query[i] > query[last_index])
			{
				large_query[l_index] = query[i] - query[last_index] - 1;
				l_index++;
			}
		}
		
		int position = start+query[last_index];
		int position2 = start+query[first_index];
		
		query = null;
		if(small_query_length > 0) do_select(start,position2-1, small_query,query_start );
		if(large_query_length > 0) do_select(position+1,end, large_query, query_start+s_index+1 );
		
	}
}
