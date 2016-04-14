#ifndef _QUICKSORT
#define _QUICKSORT

int partition(int x[], int start, int stop, int *comp, int pivot_select);
int return_index (int x[], int start, int stop, int *comp, int pivot_select);

inline void swap(int &x, int &y)
{
  int t; t=x; x=y; y=t;
}

inline void sort2(int x[], int *comp)
{
  if(x[0]>x[1]) {*comp= *comp+1; swap(x[0],x[1]);}
}

inline void sort3(int x[], int *comp) // 3 comparisons, 2.5 on average
{
  sort2(x, comp);
  if(x[1]>x[2]) { *comp= *comp+1; swap(x[1],x[2]); sort2(x, comp); }
}

inline void sort4(int x[], int *comp) // 5 comparisons
{
  sort2(x, comp); sort2(x+2, comp);
  if(x[0]>x[2]) {*comp= *comp+1; swap(x[0],x[2]);}
  if(x[1]>x[3]) {*comp= *comp+1; swap(x[1],x[3]);}
  sort2(x+1, comp);
}

// this one gets 7.5 comps on average (7 is optimal)
// hopefully with fewer data movements to make it faster
inline void sort5(int x[], int *comp)
{
  sort4(x, comp);
  int tmp=x[4];
  for(int i=3; i>=0; i--)
    if(x[i]>tmp) {*comp= *comp+1;  x[i+1]=x[i];}
    else {*comp= *comp+1; x[i+1]=tmp; return; }
  x[0]=tmp;
}

#include "pivot.h"
int select6 (int A[], int start, int stop, int input, int *comp)
{
	 int pivot_policy = 3;

    int rank=input, x=input;
    // base cases
    if(start>=stop) // interval length is 0 or 1
    {
        rank=start;
        *comp = *comp+1;
		  if(x>A[rank]) {rank++;}
        return rank;
    }
    if(stop-start<=4)
    {
      switch(stop-start)
      {
        case 1: sort2(A+start, comp); break;
        case 2: sort3(A+start, comp); break;
        case 3: sort4(A+start, comp); break;
        case 4: sort5(A+start, comp); break;
      }
      return rank;
    }
    // recursive case
    //cout<<"g "<<comparision<<" ";
    int pivotpos=partition(A,start,stop, comp, pivot_policy);
    //if(comp++ && pivotpos==rank) return rank;
    //*comp = *comp +1;
	 if(pivotpos==rank) return rank;

	// *comp = *comp+1;
    if(rank<pivotpos) return select6(A, start,pivotpos-1,rank,comp);
    else return select6(A, pivotpos+1,stop,rank,comp);
    

}
int return_index (int x[], int start, int stop, int *comp, int pivot_select)
{
  if(pivot_select == 3)
  { 
   int pivot = start;
   return x[choose(x,start,stop, comp, pivot_select)];
  }
  else
  {
     choosepivot(x, start, stop, comp, pivot_select);
     return x[stop];
  }
}
int partition(int x[], int start, int stop, int *comp, int pivot_select)
{
  int pivot = start;
  if(pivot_select !=3)
  {
   int posit = choose(x,start,stop, comp, pivot_select);
  	pivot = x[posit];
  	//choosepivot(x, start, stop, comp, pivot_select);
	//pivot = x[stop];
  }
  else
  {
  	 int num_median = (stop-start+1)/5;
	 int *median_arr = new int[num_median];
	 for(int i=0; i<num_median; i++)
	 {
	 	int sub_start = start+i*5;
		int sub_end = start+(i*1)*5-1;
		int sub_find = sub_start + 3;
		if(sub_find > stop ) sub_find  = stop;
		if(sub_end > stop) sub_end = stop;
	 	median_arr[i] = x[select6(x, sub_start, sub_end, sub_find, comp)];
		//cout<<"median"<<median_arr[i]<<endl; 
	 }
	 //for(int i=0; i<num_median; i++) cout<<median_arr[i]<<endl;
    int find_pos = num_median/2+1;
	 if(find_pos > num_median-1) find_pos = num_median-1;
	 int value =median_arr[select6(median_arr, 0, num_median-1, find_pos, comp)];
	 int pos = 0;
	 //cout<<"value"<<value<<endl;
	 for(int i=start; i<=stop; i++)
	 {
	 	if(value == x[i])
		{
			pos = i;
			break;
		}
	 }
	 swap (x[pos], x[stop]);
	 pivot = x[stop];
	 //pivot = x[pos];
	//cout<<pivot<<endl;
  }
  int left, right;
  if(pivot_select !=3)
    left=start, right=stop;
  else
    left=start, right=stop-1;

  /*cout<<"pivot "<<pivot<< " before" ;
  cout<<endl;
  for(int i =start; i<=stop; i++) cout<<x[i]<<" ";
  cout<<endl;
*/
  while(left<right)
  {
    //*comp= *comp+1;     
    while(x[left]<pivot){*comp = *comp+1; left++;}
    while(right>start && x[right]>=pivot){*comp=*comp+1; right--;}
    if(left<right) {swap(x[left],x[right]);}
  }
  /*cout<<"after" ;
  cout<<endl;
  for(int i =start; i<=stop; i++) cout<<x[i]<<" ";
  cout<<endl;
*/
  if(pivot_select == 3)
   swap(x[left],x[stop]);
  
  return left;
}

void quicksort(int x[], int start, int stop, int *comp, int pivot_select)
{
  if(stop-start<=4)
  {
    //*comp= *comp+1;     
    if(start>=stop){/**comp= *comp+1;*/ return;}
    switch(stop-start)
    {
      case 1: sort2(x+start, comp); return;
      case 2: sort3(x+start, comp); return;
      case 3: sort4(x+start, comp); return;
      case 4: sort5(x+start, comp); return;
    }
  }
  //cout<<stop<<endl;
  int pivotpos = partition(x,start,stop, comp, pivot_select);
  //for(int i =start; i<=stop; i++) cout<<"a"<<x[i]<<" ";
  //cout<<endl;
  //cout<<pivotpos<<endl;
  quicksort(x,start,pivotpos-1, comp, pivot_select);
  quicksort(x,pivotpos+1,stop, comp, pivot_select);
}

void quicksort(int x[], int len, int *comp, int pivot_select)
  { quicksort(x,0,len-1, comp, pivot_select); }

#endif
