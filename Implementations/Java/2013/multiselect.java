import java.io.*;
import java.util.*;
public class multiselect {
	
	public static void main ( String args[]) throws IOException
	{
		//Input array size
		int size_A = (int) Math.pow(2, 17);
		int A[] = new int[size_A];
		
		//Pivot type (default: first element)
		int pivot_type = 0;
		
		Scanner sc = new Scanner(System.in);
		System.out.println("input array size : " + size_A);
		//input array type (0:decreasing, 1:uniform random (no duplicate) )
		System.out.println("input array type (0:decreasing, 1:uniform random):" );
		int array_type=sc.nextInt();
		if(array_type == 0)
		{
			for(int i = 0; i<size_A; i++) A[i] = size_A-i-1;
		}
		else
		{
			int temp_array[] = new int[size_A];
			for(int i=0; i<size_A; i++ ) temp_array[i] = i;
			Random aRandom = new Random();
			for(int i = 0; i<size_A; i++)
			{
				int temp_index = aRandom.nextInt(size_A-i);
				A[i] = temp_array[temp_index];
				int temp = temp_array[size_A-1-i];
				temp_array[temp_index] = temp; 	
			}
		}
		
		//infinite loop
		while(true)
		{
			 
			//Query type (0:evenly spaced, 1: uniform random , 2: Gaussian (N/2, N/4), 3: Gaussian (N/2. N/8), 4: exponential(16/N)
			System.out.println("Query type (0:evenly spaced, 1: uniform random , 2: Gaussian (N/2, N/4), 3: Gaussian (N/2. N/8), 4: exponential(16/N)");
			int query_type = sc.nextInt();
			if(query_type == -1) break;
			while(true)
			{
				//Pivot type (0: first elemet, 1: random, 2: median of 3, 3: median of medians (real median)
				System.out.println("Pivot type (0: first elemet, 1: random, 2: median of 3, 3: median of medians (real median)");
				pivot_type = sc.nextInt();
				if(pivot_type == -1) break;
				//create query array and do main work
				
				for(int size_Q = size_A/2; size_Q >= 32; size_Q=size_Q/2)
				{
					//print query size
					System.out.println("number of queries : " + size_Q);
					
					int Q[] = new int[size_Q];
					
					//fill query array
					if(query_type == 0)
					{
						int gap = size_A/size_Q;
						for(int i =0; i<size_Q && gap*i < size_A ; i++) Q[i] = size_A-gap*i-1;
					}
					else if(query_type ==1)
					{
						Random aRandom = new Random();
						for(int i =0; i<size_Q; i++) Q[i] = aRandom.nextInt(size_A);
					}
									
					else if(query_type == 2)
					{
						StdRandom bRandom = new StdRandom();
						bRandom.setSeed(System.currentTimeMillis ());
						for(int i = 0; i<size_Q; i++)
						{
							Q[i] = (int)bRandom.gaussian(size_A/2, size_A/4);
							if(Q[i]<0 || Q[i] >= size_A) {i--; continue;}

						}
					}
					else if(query_type ==3)
					{
						StdRandom bRandom = new StdRandom();
						bRandom.setSeed(System.currentTimeMillis ());
						for(int i = 0; i<size_Q; i++)
						{
							Q[i] = (int)bRandom.gaussian(size_A/2, size_A/8);
							//System.out.println(Q[i]);
							if(Q[i]<0 || Q[i] >= size_A) {i--; continue;}

						}
					}
					else
					{
						StdRandom bRandom = new StdRandom();
						bRandom.setSeed(System.currentTimeMillis ());
						for(int i = 0; i<size_Q; i++)
						{
							Q[i] = (int)(size_A*(double)bRandom.exp(16));
							//System.out.println(Q[i]);
							if(Q[i]<0 || Q[i] >= size_A) {i--; continue;}

						}
					}
					
					//sort the query array
					Arrays.sort(Q);
					
					/*print order
					 * 0.number of query elements
					 * 1.entropy
					 * 2.merge sort
					 * 3.quick sort
					 * 4.Dobkin-Munro
					 * 5.Simple online
					 * 6.Kaligosi et.al
					 * 7.Optimal online
					 */
					
					//calculate the entropy
					double entropy = 0.0;
					for(int i =0; i<=size_Q; i++)
					{
						if((i==0 && Q[0] == 0) || (i > 0 && i<size_Q && Q[i] == Q[i-1]) || (i == size_Q && size_A == Q[i-1])  ) 
							entropy = entropy + 0;
						else if(i== 0 && Q[0] != 0)
							entropy = entropy +  Q[i]*(Math.log((double)size_A/Q[i])/Math.log(2));
						else if (i == size_Q)
							entropy = entropy + (size_A-Q[i-1])*(Math.log((double)size_A/(size_A-Q[i-1]))/Math.log(2));
						else
							entropy = entropy + (Q[i]-Q[i-1])*(Math.log((double)size_A/(Q[i]-Q[i-1]))/Math.log(2));
					}

					System.out.println("----------------------");
					System.out.println(entropy);
					//merge sort
					mergesort merge = new mergesort(A, size_A);
					System.out.println(merge.num_comparision);
					
					//quick sort
					quicksort quick = new quicksort(A, size_A, pivot_type);
					System.out.println(quick.num_comparison);
					
					//Dobkin-Munro
					DobkinMunro offline1 = new DobkinMunro(A, size_A, pivot_type);
					offline1.select(Q, size_Q);
					System.out.println(offline1.num_comparison);
					
					//Kaligosi et. al
					Kaligosi offline2 = new Kaligosi(A, size_A, pivot_type);
					offline2.select(Q, size_Q, entropy);
					System.out.println(offline2.num_comparison);
				
					//simple online
					Simple_Online online1 = new Simple_Online(A, size_A, pivot_type);
					for(int i = 0; i<size_Q; i++)
					{
						online1.select(Q[i]);
						int value = online1.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online1.num_comparison);
					
					//optimal online
					Optimal_Online online2 = new Optimal_Online(A, size_A, pivot_type, 0);
					for(int i = 0; i<size_Q; i++)
					{
						online2.select(Q[i]);
						//int value = online2.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online2.num_comparison);
					
					//optimal online with variant length of initial runs (only increasing)
					Optimal_Online online3 = new Optimal_Online(A, size_A, pivot_type, 1);
					for(int i = 0; i<size_Q; i++)
					{
						online3.select(Q[i]);
						//int value = online3.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online3.num_comparison);
					
					//optimal online with variant length of initial runs (increasing and decreasing)
					Optimal_Online online4 = new Optimal_Online(A, size_A, pivot_type, 2);
					for(int i = 0; i<size_Q; i++)
					{
						online4.select(Q[i]);
						//int value = online3.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online4.num_comparison);
					
					//optimal online with variant length of initial runs and set l as max(l_in_original_optimal_online, longest run length);
					Optimal_Online online5 = new Optimal_Online(A, size_A, pivot_type, 3);
					for(int i = 0; i<size_Q; i++)
					{
						online5.select(Q[i]);
						//int value = online3.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online5.num_comparison);
					
					//optimal online with variant length of initial runs and set l as max(l_in_original_optimal_online, longest run length);
					Optimal_Online online6 = new Optimal_Online(A, size_A, pivot_type, 4);
					for(int i = 0; i<size_Q; i++)
					{
						online6.select(Q[i]);
						//int value = online3.select(Q[i]);
						//System.out.println("query " + Q[i] + " answer " + value);
					}
					System.out.println(online6.num_comparison);
					
					System.out.println("----------------------");
					merge = null;
					quick = null;
				}
			}
		}
	}
}
