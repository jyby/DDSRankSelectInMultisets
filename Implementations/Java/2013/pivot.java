//pivot selection class
/*
 * Pivot_policy
 * 0: first element
 * 1: random
 * 2: median of 3
 * 3: median of medians (real median)
 * only median of medians finds 'real' median in all selection algorithms at once
 */
import java.util.*;
public class pivot {
	int pivot = 0;
	int pivot_index = 0;
	int num_comparison = 0;
	public pivot(int A[], int start, int end, int pivot_policy)
	{
		this.pivot = pivot_policy;
		this.pivot_index = start;
		num_comparison = 0;
		if(pivot_policy == 0) first_pivot(A, start, end);
		if(pivot_policy == 1) random_pivot(A, start, end);
		if(pivot_policy == 2) median_of3(A, start, end);
		if(pivot_policy == 3) median_of_medians(A, start, end);
		
	}
	public void first_pivot(int A[], int start, int end)
	{
		this.pivot_index = start;
	}
	public void random_pivot(int A[], int start, int end)
	{
		Random aRandom = new Random();
		//System.out.println(start+" "+ end);
		this.pivot_index = aRandom.nextInt(end-start+1)+start;
	}
	public void median_of3(int A[], int start, int end)
	{
		int mid=(start+end)/2;
		this.num_comparison++;
		if(A[start]<=A[mid])
		{
			this.num_comparison++;
			if(A[mid]<=A[end]) this.pivot_index = mid;
			else if(A[end]<=A[start]) {this.num_comparison++; this.pivot_index = start;}
			else {this.num_comparison++; this.pivot_index = end;}
			return;
	    }
	    // so A[mid]<A[start]
		this.num_comparison++;
		if(A[start]<=A[end]) this.pivot_index = start;
	    else if(A[end]<=A[mid]){this.num_comparison++; this.pivot_index = mid;}
	    else {this.num_comparison++; this.pivot_index = end;}
	}
	public void median_of_medians(int A[], int start, int end)
	{
		//System.out.println("largest: " + (int)((end-start+1)/2));
		//System.out.println("a: "+find(A, start, end-start+1, (int)((end-start+1)/2)));
		
		find(A, start,end-start+1, (int)((end-start+1)/2));
		this.pivot_index = start+(int)((end-start+1)/2)-1;
		
		//System.out.println("pindex: "+pivot_index);
	}
	
	/*find median of medians
	 * ref: http://yiqi2.wordpress.com/2013/07/03/median-of-medians-selection-algorithm/
	 */
	private int find(int[] a, int s, int n, int k ) 
	{
		int end = n-1+s;
	    // start point s, length n, find k-th number
	    if ( n == 1 && k == 1 )
	        return a[s];
	    
	    if(n <=5)
	    {
	    	smallsort s3 = new smallsort(a, s, end);
        	this.num_comparison = this.num_comparison + s3.num_comparison;
        	return a[s+k-1];
	    }
	    
	    int m = (n+4) /5;
	    int[] mid = new int[m];
	    //System.out.println(" s: "+s+"n: "+n+" m: "+m+" end: "+end+" k: "+k);
	    for (int i=0; i<m; i++) {
	        int t = s+i*5;      // 5-elements block pointer
	        if ( end-t > 4 ) {
	        	
	        	smallsort s1 = new smallsort(a, t, t+4); // sort 5 elements
	        	
	        	this.num_comparison = this.num_comparison + s1.num_comparison;
	            //sort(a, t, 5);      
	            mid[i] = a[t+2];
	            s1 = null;
	        }
	        else {      // less than 5 left
	        	smallsort s2 = new smallsort(a, t, end); // sort the rest
	        	this.num_comparison = this.num_comparison + s2.num_comparison;
	            //sort(a, t, n-t);    
	            mid[i] = a[(t+end)/2];
	            s2 = null;
	        }	        
	    }

	   /* System.out.println("origisnal");
        for(int i = s; i<=end; i++) System.out.print(a[i]+" ");
        System.out.println("");
        
	    System.out.println("median array");
	    for(int i = 0; i<m; i++) System.out.print(mid[i]+" ");
	    System.out.println("");
	    */
	    int pivot = find(mid, 0, m, (m+1)/2);
	    //System.out.println("pivot : " + pivot);
	    for (int i=0; i<n; i++) {        // find pivot location
	    	if (a[s+i] == pivot ) {
	            swap(a, s+i, s+n-1);
	            break;
	        }
	    }
	     
	    int pos = 0;
	    for (int i=0; i<n-1; i++) {      // using pivot to part
	    	this.num_comparison++;
	    	if ( a[s+i] < pivot ) {
	            if ( i != pos )
	                swap(a, s+i, s+pos);
	            pos++;
	        }
	    }
	    swap(a, s+pos, s+n-1);
	   
	    /*System.out.println("1st : " + pos); 
	    System.out.println("after parti"); 
	    for(int i = s; i<=end; i++) System.out.print(a[i]+" ");
	    System.out.println("");
	    */
	    if ( pos == k-1 )
	    	return pivot;
	    else if ( pos > k-1 )
	        return find(a, s, pos, k);
	    else
	        return find(a, s+pos+1, n-pos-1, k-pos-1);
	}
	public void swap(int A[], int i, int j)
	{
		int temp = A[i];
		A[i] = A[j];
		A[j] = temp;
	}
}
