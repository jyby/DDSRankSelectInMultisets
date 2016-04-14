#ifndef _ONLINE
#define _ONLINE

#include "Bitvector.h"

#include "quicksort.h"

class online
{
  BitvectorP bit; // array of bits
  int *A;         // array of ints
  int len;
  int *d;  // array of pivot depths
  int comparision; // number of comparision
  int select_call;
  int pivot_select;
  const static bool dodepth=false;

public:

  online(int Ain[], int Alen, int pivot): bit(Alen)
  {
    A=Ain;
    comparision = 1;
	 select_call = 0;
    pivot_select = pivot;
    len=Alen;
//    bit.setsize(len);
//cout << "bit vector allocated\n";
    bit.clearall();
    minmax();
//cout << "minmax() called\n";
    if(dodepth)
    {
      d = new int[len];
      for(int i=1; i+1<len; i++) d[i]= -1;
      d[0]=d[len-1]=0;
    }
    else d=NULL;
  }
  inline int sel() {return select_call;}
  inline int comp() {return comparision;}
  inline int num1s() { return bit.count(); }
  inline int setcomp(int i) {comparision = i;}

  ~online() { if(d!=NULL) delete [] d; }

  int select(int rank) // 0<= rank < len
  {
    if(rank<0) 
    {
	rank=0;
    }
    if(rank>=len)
    {
     	rank=len-1;
    }
    if(bit[rank]) return A[rank]; // easy case

    // find left and right borders
    int start=rank, stop=rank;
    while(!bit[start]) start--;
    start++;
    while(!bit[stop]) stop++;
    stop--;
	 //select_call ++;
    select(start, stop, rank, true);
    return A[rank];
  }

  int rank(int x) // returns # of items y in A with y<x
  {
    // we've found min and max, so make sure x is in range first
    //comparision++;
    if(comparision++ && x<=A[0]) {return 0;}
    //comparision++;
    if(comparision++ && x>A[len-1]) { return len;}
    //comparision++;
    if(comparision++ && x==A[len-1]) { return len-1;}

    // binary search to find interval that might hold x
    int start=1, stop=len-1;
    while(start+1<stop)
    {
      int mid=(start+stop)/2;
//cout << "RANK: start, stop, mid"<< start << stop << mid << endl;
      if(comparision++ && x<A[mid]) { stop=mid-1;}
      else if(comparision++ && x>A[mid]) {start=mid+1;}
      else /*if(x==A[mid])*/ start=stop=mid;
    }
  //  if(start!=stop) start=stop; // in case they crossed

    // find endpoints of unsorted interval
    while(!bit[start]) start--;
    start++;
    while(!bit[stop]) stop++;
    stop--;

    // need to make sure A[start-1]<x<A[stop+1] here
    
    if(comparision++ && x==A[start-1]) {return start-1;}
    if(comparision++ && x==A[stop+1]) {return stop+1;}

//cout << "RANK: start, stop, x"<< start << stop << x << endl;

    return select(start,stop,x,false);
  }

private:

  inline int max(int x, int y) { return x>y?x:y; }

  // invariant1: bit[start-1]==bit[stop+1]==1 and start<=rank<=stop
  // invariant2: bit[start-1]==bit[stop+1]==1 and A[start-1]<x<A[stop+1]
  //   returns the rank
  int select(int start, int stop, int input, bool byrank)
  {
    int fake = 0;
    bool byvalue=!byrank;
    int rank=input, x=input;
    // base cases
	 if(start>=stop) // interval length is 0 or 1
    {
      if(byvalue)
      { 
        rank=start;
        if(comparision++ && x>A[rank]) {rank++;}
      }
      if(!bit[rank]){
        if(dodepth)
          { d[rank]=1+max(d[start-1],d[stop+1]); }
        bit.set(rank); 
      }
      return rank;
    }
    if(stop-start<=4)
    {
      switch(stop-start)
      {
        case 1: sort2(A+start, &comparision); break;
        case 2: sort3(A+start, &comparision); break;
        case 3: sort4(A+start, &comparision); break;
        case 4: sort5(A+start, &comparision); break;
      }

      bit.set(start);
      if(dodepth)
        { d[start]=1+max(d[start-1],d[stop+1]);
          for(int i=start+1; i<=stop; i++) { d[i]=d[i-1]; bit.set(i); }
        }
      else
        for(int i=start+1; i<=stop; i++) { bit.set(i); }

      if(byvalue)
      { 
        rank=start;
        while(comparision++ && x>A[rank]){rank++;}
      }

      return rank;
    }
    // recursive case
    //cout<<"g "<<comparision<<" ";
    int pivotpos=start;
	 int sub_start = start;
	 int sub_stop = stop;
	 /*while(pivotpos != (start+stop)/2)
	 {
	 	pivotpos=partition(A,sub_start,sub_stop, &comparision, pivot_select);
    	//cout<<sub_start<<" "<<sub_stop<<" "<<(start+stop)/2<<" "<<pivotpos<<endl;
		bit.set(pivotpos);
		if(pivotpos > (start+stop)/2 ) sub_stop = pivotpos-1;
		else sub_start = pivotpos+1;

    }*/
	 pivotpos=partition(A,start,stop, &comparision, pivot_select);
	 bit.set(pivotpos);

	 //cout<<comparision<<endl;
    if(dodepth)
      { d[pivotpos]=1+max(d[start-1],d[stop+1]); }
    
    if(byrank && pivotpos==rank) return rank;
    if(byvalue && comparision++ && A[pivotpos]==x) return pivotpos;

    if(byrank)
    {
	 	select_call = select_call+(stop-start+1);
      //comparision++;
      if(rank<pivotpos) return select(start,pivotpos-1,rank,true);
      else return select(pivotpos+1,stop,rank,true);
    }
    else // byvalue
    {
	 	select_call++;
      //comparision++;
      if(x<A[pivotpos]) return select(start,pivotpos-1,x,false);
      else return select(pivotpos+1,stop,x,false);
    }
  }

  void swap(int i, int j)
  {
    int tmp=A[i];
    A[i]=A[j];
    A[j]=tmp;
  }

  void minmax()
  {
    int minpos, maxpos;
    //comparision++;
    if(comparision++ && A[0]<A[1]) {maxpos=1; minpos=0;}
    else {maxpos=0; minpos=1;}

    int lo, hi;

    for(int i=2; i+1<len; i+=2)
    {
      lo=i; hi=i+1;
      //comparision = comparision+3;
      if(comparision++ && A[i]>A[i+1]) {lo=i+1; hi=i;}

//cout <<i<<" "<<A[lo]<<" "<<A[hi]<<" "<<lo<<" "<<hi<<" "<<len<< endl;

      if(comparision++ && A[lo]<A[minpos]) minpos=lo;
      if(comparision++ && A[hi]>A[maxpos]) maxpos=hi;
    }
    lo=hi=len-1;
    //comparision = comparision + 2;
    if(comparision++ && A[lo]<A[minpos]) minpos=lo;
    if(comparision++ && A[hi]>A[maxpos]) maxpos=hi;

    swap(0,minpos);
    //comparision++;
    if(maxpos==0) swap(minpos,len-1);
    else swap(maxpos,len-1);
    bit.set(0);  bit.set(len-1);
  }

public:
  void print(ostream & os, bool printA=false) const
  {
    if(printA)
    for(int i=0; i<len; i++)
    {
      os << A[i] << " " << endl;
      //if(i%10==9) os << endl;
    }
    os << endl << bit;
    if(dodepth)
      for(int i=0; i<len; i++)
      {
        if(d[i]<0) cout << " ";
        else if(d[i]<10) cout << d[i];
        else if(d[i]<36) cout << (char)('a'+(d[i]-10));
        else cout << "+";
        if(i%80==79) cout << endl;
      }
    cout << endl; // << bit.count() << endl;
  }

};

#endif
