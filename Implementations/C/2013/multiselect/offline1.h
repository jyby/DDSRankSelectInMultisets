#ifndef _OFFLINE1
#define _OFFLINE1

#include "quicksort.h"
int pivot_policy = -1;;
int select_partition (int A[], int start, int end, int index, int *comp)
{
	int value = A[index];
	swap(A[index], A[end]);
	int store_index = start;
	for(int i = start; i<end; i++)
	{
		*comp= *comp+1;
		if(A[i] <=value)
		{
			swap(A[store_index], A[i]);
			store_index++;
		}
	}
	swap(A[end], A[store_index]);
	return store_index;
	
}
//find kst smallest element (quickselect)
int select (int A[], int start, int stop, int input, int *comp)
{
	/*if(start >= end || k<0) return A[start];
   //int pos=start + rand()%(end-start+1);
	//int newpivot = select_partition(A, start, end, pos, comp);
	int newpivot = partition(A,start,end, comp, 1);
	int pivotDist = newpivot-start;
	//cout<<pivotDist;
	if(pivotDist == k){return A[newpivot];}
	else if ( k < pivotDist){return select (A, start, newpivot-1, k, comp);}
	else {return select(A,newpivot+1, end, k-pivotDist, comp);}*/
    int rank=input, x=input;
    // base cases
    if(start>=stop) // interval length is 0 or 1
    {
        rank=start;
        *comp = *comp+1;
		  if(x>A[rank]) {rank++;}
        return rank;
    }
	 int fake=0;
    if(stop-start<=4)
    {
      switch(stop-start)
      {
        case 1: sort2(A+start, &fake); break;
        case 2: sort3(A+start, &fake); break;
        case 3: sort4(A+start, &fake); break;
        case 4: sort5(A+start, &fake); break;
      }
		//cout<<fake<<endl;
		
		*comp = *comp + fake;
     
	  return rank;
    }
    // recursive case
    //cout<<"g "<<comparision<<" ";
    int pivotpos=partition(A,start,stop, &fake, pivot_policy);
	 
	 *comp = *comp + fake;
    
	 
	 // if(comp++ && pivotpos==rank) return rank;
    //*comp = *comp +1;
	 if(pivotpos==rank) return rank;
    //*comp = *comp+1;
    if(rank<pivotpos) return select(A, start,pivotpos-1,rank,comp);
    else return select(A, pivotpos+1,stop,rank, comp);
    
   
}	


int abs(int k)
{
	if(k>=0) return k;
	else return -1*k;
}

void select_offline1 (int A[], int Q[], int start, int end, int Alen_start, int Alen, int size, int *comp, int pivot)
{
	pivot_policy = pivot;
  //easy case
  //*comp= *comp+1;
  if(Alen-Alen_start-1<=4 ) 
  {
  // cout<<start<<endl;
    //*comp = *comp +1;
    select(A, Alen_start, Alen-1, Q[start], comp);
    return;
  }
  if(start>end) return;
  //find i_j which is closest to n/2
  
  int *B = new int[Alen-Alen_start];
  for(int i = 0; i<Alen-Alen_start; i++) B[i] = A[Alen_start+i];

  size = return_index(B, 0, Alen-1-Alen_start, comp, 2);

  int closest = start;
  
  for (int i = start; i<=end ; i++)
  {
 	//*comp= *comp+1;
	if(abs(Q[i]-size) < abs(Q[closest]-size)) closest = i;

  }
  

  //cout<<"before "; 
  //for(int i=Alen_start; i<Alen;i++) cout<<A[i]<<" ";
  //cout<<endl;

  //long int fake = 0;
  //*comp = *comp +1;
  int next = select(A, Alen_start, Alen-1, Q[closest], comp);
  
  //cout<<"afater ";
  //for(int i=Alen_start; i<Alen;i++) cout<<A[i]<<" ";
  //cout<<endl;
  //cout<<"center "<<Q[closest]<<" "<<A[next]<<" "<<*comp<<endl;
  
  delete []B;
   //divide Q and do as recursive
  //for(int i=closest+1; i<=end; i++)
//	Q[i] = Q[i] - Q[closest];
  select_offline1 (A, Q, start, closest-1, Alen_start , next , (Q[closest]-1)/2, comp, pivot);
  select_offline1 (A, Q, closest+1, end, next+1, Alen, (Alen+Q[closest])/2, comp, pivot);
  //cout<<*comp<< " "; 
}

#endif
