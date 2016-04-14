#ifndef _PIVOT
#define _PIVOT

// for swap()
#include "quicksort.h"

// choose one of these for the pivot method

const int pivot_default=0;
const int pivot_random=1;
const int pivot_medof3=2;
const int pivot_medofmed=3;
int find_kth(int v[], int n, int k, int *comp); 
int medofme(int A[], int *comp);
const int pivot=1;
// chooses the pivot, and swaps it to A[stop]
// hopefully optimizing compiler makes this very efficient
inline int choose(int A[], int start, int stop, int *comp, int pivot_select)
{
  if(pivot_select==pivot_default) return stop;

  if(pivot_select==pivot_random)
  {
    int pos=start + rand()%(stop-start+1);
    //swap(A[pos],A[stop]);
    return pos;
  }

  if(pivot_select==pivot_medof3)
  {
    int mid=(start+stop)/2;
    *comp = *comp + 1;
    if(A[start]<=A[mid])
    {
      *comp = *comp+1;
      if(A[mid]<=A[stop])
        {return mid;  }
      *comp = *comp+1;
      if(A[stop]<=A[start])
        {return start;  }
      return stop;
    }
    // so A[mid]<A[start]
    *comp = *comp + 1;
    if(A[start]<=A[stop])
      {return start; }
    *comp = *comp + 1;
    if(A[stop]<=A[mid])
      {return mid; }
    return stop;
  }
 return stop;
}
inline void choosepivot(int A[], int start, int stop, int *comp, int pivot_select)
{
  if(pivot_select==pivot_default) return;

  if(pivot_select==pivot_random)
  {
    int pos=start + rand()%(stop-start+1);
    swap(A[pos],A[stop]);
    return;
  }

  if(pivot_select==pivot_medof3)
  {
    int mid=(start+stop)/2;
    *comp = *comp + 1;
    if(A[start]<=A[mid])
    {
      *comp = *comp+1;
      if(A[mid]<=A[stop])
        {swap(A[mid],A[stop]); return; }
      *comp = *comp+1;
      if(A[stop]<=A[start])
        {swap(A[start],A[stop]); return; }
      return;
    }
    // so A[mid]<A[start]
    *comp = *comp + 1;
    if(A[start]<=A[stop])
      {swap(A[start],A[stop]); return; }
    *comp = *comp + 1;
    if(A[stop]<=A[mid])
      {swap(A[mid],A[stop]); return; }
    return;
  }
  //median of median
  if(pivot_select==pivot_medofmed) 
  {
		//cout<<"aa"<<stop<<" "<<start<<endl;
		int * B = new int[stop-start+1];
		for(int i = 0; i<stop-start+1; i++){B[i] = A[start+i];}
		
		int index = medofme(B, comp);

		/*int tmp = 0;
		int value = find_kth(B, stop-start+1, (stop-start+1)/2,&tmp);
		*comp = *comp + 3*(stop-start+1);
		//cout<<start+index<<" "<<A[start+index]<<endl;
		int index = 0;
		//cout<<value<<" "<<start<<" "<<stop<<endl;
		for(int i =start; i<=stop; i++)
		{
			if(A[i] == value) 
			{	
				index = i;
				break;
			}
		}
		//cout<<endl;
		//cout<<index<<endl;
		swap(A[index], A[stop]);
		return;
		*/
	//	delete [] B;


   }
}
int medofme(int A[], int * comp)
{
	return 0;
}
int minisec(int *v, int n, int k, int *comp)
{
		if (n == 1 && k == 0) return v[0];
		//cout<<n;	
		int m = (n + 4)/5;
		int *medians = new int[m];
		for (int i=0; i<m; i++) 
		{
			if (5*i + 4 < n) 
			{
				int *w = v + 5*i;
		  		for (int j0=0; j0<3; j0++) 
				{
		  			int jmin = j0;
		  			for (int j=j0+1; j<5; j++) 
					{
						*comp = *comp +1;
		  				if (w[j] < w[jmin]) jmin = j;
		  			}
		  			swap(w[j0], w[jmin]);
		  		}
		  		medians[i] = w[2];
				medians[i] = v[5*i];
			} 
			else 
			{
		  		medians[i] = v[5*i];
		  	}
		}
		int pivot = minisec(medians, m, m/2, comp);
		delete [] medians;

		for (int i=0; i<n; i++) 
		{
			*comp = *comp +1;
			if (v[i] == pivot) 
			{
				swap(v[i], v[n-1]);
				break;
			}
		}
			
		int store = 0;
		for (int i=0; i<n-1; i++) 
		{
			*comp = *comp+1;
			if (v[i] < pivot) 
			{
				swap(v[i], v[store++]);
			}
		}
		swap(v[store], v[n-1]);
		
		if (store == k) 
		{
			return pivot;
		} 
		else if (store > k) 
		{
			return minisec(v, store, k, comp);
		} 
		else 
		{
			return minisec(v+store+1, n-store-1, k-store-1, comp);
		}

}
	int find_kth(int *v, int n, int k, int *comp) 
	{
		if (n == 1 && k == 0) return v[0];
		//cout<<n;	
		int m = (n + 4)/5;
		int *medians = new int[m];
		for (int i=0; i<m; i++) 
		{
			if (5*i + 4 < n) 
			{
				int *w = v + 5*i;
		  		for (int j0=0; j0<3; j0++) 
				{
		  			int jmin = j0;
		  			for (int j=j0+1; j<5; j++) 
					{
						*comp = *comp +1;
		  				if (w[j] < w[jmin]) jmin = j;
		  			}
		  			swap(w[j0], w[jmin]);
		  		}
		  		medians[i] = w[2];
				medians[i] = v[5*i];
			} 
			else 
			{
		  		medians[i] = v[5*i];
		  	}
		}
			
		int pivot = minisec(medians, m, m/2, comp);
		//delete [] medians;
		return pivot;	
	}


#endif
