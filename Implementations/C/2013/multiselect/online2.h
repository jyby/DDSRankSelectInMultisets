#ifndef _ONLINE2
#define _ONLINE2

#include "Bitvector.h"

#include "quicksort.h"

class online2
{
  BitvectorP bit; // array of bits
  BitvectorP W;
  int *A;         // array of ints
  int len;
  int *d;  // array of pivot depths
  int comparision; // number of comparision
  int pivot_select;
  const static bool dodepth=true;

public:

  online2 (int Ain[], int Alen, int pivot): bit(Alen)
  {
    A=Ain;
    comparision = 1;
    pivot_select = pivot;
    len=Alen;
//    bit.setsize(len);
//cout << "bit vector allocated\n";
    bit.clearall();
 	 W.setsize(len);
	 W.clearall();
	 for(int i = 0; i<len; i++) W.set(i);
    minmax();
//cout << "minmax() called\n";
    if(dodepth)
    {
      d = new int[len];
      for(int i=1; i+1<len; i++) d[i]= -1;
      d[0]=d[len-1]=0;
    }
    else d=NULL;
  	//cout<<comparision<<endl;
  }
  inline int comp() {return comparision;}
  inline int num1s() { return bit.count(); }
  inline int setcomp(int i) {comparision = i;}
  ~online2 () { if(d!=NULL) delete [] d; }

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

	 //calculate l
	 int k = rank;
	 for(k = rank ; d[k]==-1; k++){}
	 int  l = 1+(int)(log((double)d[k]+1)/log(2));
	 //cout<<rank<<" "<<d[k]<<" "<<l<<endl;	
    //cout<<rank<<endl; 	  	
    select(start, stop, rank, l, true);
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
	 /*int k = rank;
	 for(int k = rank ; d[k]==-1; k++){}
	 int  l = 1+(int)(log((double)d[k]+1)/log(2));*/

    return select(start,stop,x,1, false);
  }

private:

  inline int max(int x, int y) { return x>y?x:y; }

  // invariant1: bit[start-1]==bit[stop+1]==1 and start<=rank<=stop
  // invariant2: bit[start-1]==bit[stop+1]==1 and A[start-1]<x<A[stop+1]
  //   returns the rank
  int select(int start, int stop, int input, int l,  bool byrank)
  {
    int fake = 0;
    bool byvalue=!byrank;
    int rank=input, x=input;
/*	cout<<start<<" "<<stop<<" "<<rank<<endl;
	cout<<"array ";
	for(int i=start;i<=stop;i++) cout<<A[i]<<" ";
	cout<<endl;*/
    // base cases
	 int kr = rank;
	 for(kr = rank ; d[kr]==-1; kr++){}
	 l = 1+(int)(log((double)d[kr]+1)/log(2));
	 
    int gr = rank;
	 for(gr = rank ; d[gr]==-1; gr--){}
	 int l2= 1+(int)(log((double)d[gr]+1)/log(2));
    if(l2>l) l =l2;

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
	 int run = 0;
	 for(int i = start; i<=stop; i++)
	 {
	 	if(W[i]) run++;
	 }
	 //make a temp array for testing
    vector<int> * C;
	 C = new vector<int>[run];
	 int first = start;
	 int temp = 0;
	 for(int i =0; i<run; i++)
	 {
	 	temp = 0;
	 	while(temp==0 || !W[first])
		{
	 		C[i].push_back(A[first]);
			first++;
			temp++;
		}
	 }
	 //cout<<"first "<<first<<" "<<stop<<endl;
    //if stop-start<=41^2, merge (set all bits as 1)
	 int bound = 4*l*l;
	 if(stop-start+1 < bound)
	 {
		//cout<<bound<<endl;
	 	if(stop-start<=4)
		{
	 		switch(stop-start)
      	{
        		case 1: sort2(A+start, &comparision); break;
        		case 2: sort3(A+start, &comparision); break;
        		case 3: sort4(A+start, &comparision); break;
        		case 4: sort5(A+start, &comparision); break;
      	}
		}
		else
		{
			compall(C, run);
			//quicksort(A, start, stop, &comparision,3);
		}
      bit.set(start);
      if(dodepth)
        { d[start]=1+max(d[start-1],d[stop+1]);
          for(int i=start+1; i<=stop; i++) { d[i]=d[i-1]; bit.set(i); }
        }
      else
        for(int i=start+1; i<=stop; i++) { bit.set(i); W.clear(i); }

      if(byvalue)
      { 
        rank=start;
        while(comparision++ && x>A[rank]){rank++;}
      }
		
      return rank;
		
	 }

	 //merge runs until at most 1 run is < l
	 int one = -1;
	 int two = -1;
	 int count = -1;
	 int smallest = 1;
	 while(1)
	 {
	 	for(int i=0; i<run; i++)
	 	{
	 		if(C[i].size() <= l && (count==-1 || C[i].size() <C[one].size() ) )
			{
				one  = i;
				if(count == -1) count++;
				if(C[one].size()==smallest) break;

			}
		}
		if(count<0) break;
		for(int i = 0; i<run; i++)
		{
			if(i!=one && C[i].size() <= l && (count==0 || C[i].size() <C[two].size() ) )
			{
				two  = i;
				if(count ==0) count++;
				if(C[two].size()==smallest) break;

			}
		}
		if(count <1) break;
		else
		{
			if(C[one].size() <C[two].size()) smallest = C[two].size();
			else smallest = C[one].size();
			

			//cout<<l<<" "<<one<<" "<<two<<"  "<<endl;//C[2].at(0)<<" "<<C[2].size()<<" "<<C[47].size()<<endl;
			//merge one and two
			comptwo(C[one], C[two]);

			vector<int> temp1(C[one].size()+C[two].size());
			merge(C[one].begin(), C[one].end(), C[two].begin(), C[two].end(), temp1.begin());
			//cout<<C[one].size()<<" "<<C[two].size()<<" "<<temp1.size()<<" "<<C[j-1].size()<<" "<<endl;	
			vector<int> temp2(C[run-1].size());
			temp2.clear();
			temp2.assign(C[run-1].begin(), C[run-1].end());
					
			C[one].clear();
			C[one].assign(temp1.begin(), temp1.end());

			C[two].clear();
			C[two].assign(temp2.begin(), temp2.end());
			//cout<<C[i].size()<<" "<<C[k].size()<<endl;
			run--;
			count=-1;
			one = -1;
			two = -1;
			
			/*cout<<"midofmid ";
			for(int i =0; i<run; i++)
			{
				for(int k =0; k<C[i].size(); k++)
				{
					cout<<C[i].at(k)<<" ";
				}
			}
			cout<<endl;*/

		}
	 }
    //find median of medians in runs
	 int *median_array;
	 int median_index = 0;
	 median_array = new int[run];
	 for(int i =0; i<run; i++) median_array[i] = C[i].at(C[i].size()/2);	
	 /*median_index = select4 (median_array, 0, run-1, run/2);
     int stand = median_array[median_index];
	 */
	 
	 //cout<<"sdfs"<<comparision<< " ";
    int stand = return_index (median_array, 0, run-1, &comparision, 2);
	 //cout<<"werwr"<<comparision<<endl;
	 
	 //cout<<"stand :"<<stand<<endl; 
	 //partition runs
	 vector<int> *C1;
	 vector<int> *C2;
  	 C1 = new vector<int>[run];
	 C2 = new vector<int>[run];
	
	 int num_c1 = 0;
	 int num_c2 = 0;
	
	int tem1 = 0;
	int tem2 = 0;
	int qstand = 0;
	/*cout<<"array middle ";
	for(int i =0; i<run; i++)
	{
		for(int k =0; k<C[i].size(); k++)
		{
			cout<<C[i].at(k)<<" ";
		}
	}
	cout<<endl;
	*/
	
	for(int i =0; i<run; i++)
	{
		for(int k =0; k<C[i].size(); k++)
		{
			if(C[i].at(k) <stand)
			{
				C1[num_c1].push_back(C[i].at(k));
				tem1++;
				qstand++;
				//comparision++;
			}
			if(C[i].at(k) > stand)
			{
				C2[num_c2].push_back(C[i].at(k));
				tem2++;
				//comparision++;
			}	
		}
		comparision = comparision + (int)log(C[i].size())/log(2);
		if(tem1 != 0)
		{
			num_c1++;
			tem1=0;
		}
		if(tem2 != 0)
		{
			num_c2++;
			tem2=0;
		}
	}
	
//cout<<num_c1<<" "<<num_c2<<endl;	
   int size = 0;
	for(int i=0; i<num_c1; i++)
	{
		for(int k=0; k<C1[i].size(); k++)
		{
			A[start+size] = C1[i].at(k);
			if(k ==0) W.set(start+size);
			else W.clear(start+size);
			size++;
		}
	}
//cout<<size;	
	A[start+size] = stand;
	//cout<<"median "<<start+size<<" "<<A[start+size]<<endl;
	bit.set(start+size);
	d[start+size]=1+max(d[start-1],d[stop+1]); 

	//int  new_l = 1+(int)(log((double)d[start+size]+1)/log(2));

	size++;

	for(int i = 0; i<num_c2; i++)
	{
		for(int k=0; k<C2[i].size(); k++)
		{
			A[start+size] = C2[i].at(k);
			if(k ==0) W.set(start+size);
			else W.clear(start+size);
			size++;

			//cout<<start<<" "<< stop<<" "<<size<<endl;
		}
	}

	//delete C1;
	//delete C2;
	//delete C;
//return start;
	 //recursive call (We only need to call one-side), set bits and depth
	/*cout<<"array after ";
	for(int i=start;i<=stop;i++) cout<<A[i]<<" ";
	cout<<endl;
	cout<<"qstand "<<start+qstand<<endl;*/
	 if(rank == start+qstand ) return A[start+qstand];
	 else if(rank < start+qstand) return  select(start, start+qstand-1, rank, l,  true);
	 else return select(start+qstand+1, stop, rank, l, true);
    

	 




	// recursive case

    /*if(stop-start<=4)
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
    }*/
 
 
    // recursive case
    //cout<<"g "<<comparision<<" ";
    /*int pivotpos=partition(A,start,stop, &comparision, pivot_select);
    bit.set(pivotpos);
    //cout<<comparision<<endl;
    if(dodepth)
      { d[pivotpos]=1+max(d[start-1],d[stop+1]); }
    
    if(byrank && pivotpos==rank) return rank;
    if(byvalue && comparision++ && A[pivotpos]==x) return pivotpos;

    if(byrank)
    {
      //comparision++;
      if(rank<pivotpos) return select(start,pivotpos-1,rank,true);
      else return select(pivotpos+1,stop,rank,true);
    }
    else // byvalue
    {
      //comparision++;
      if(x<A[pivotpos]) return select(start,pivotpos-1,x,false);
      else return select(pivotpos+1,stop,x,false);
    }*/
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
  void compall(vector<int> *C1, int j)
  {
		int a =0;
		int b =0;
		int number = j;
		int next = j/2+1;
   	if(number%2 ==0) next = j/2;
		else next = j/2+1;

		if(next<2) return;
 
  		vector<int> *C2;
   	C2 = new vector<int>[next];
		//for(int i = 0; i<next ; i++)
		//	vector<int> C2[i](2*C1[i].size);
		int k = 0;

		for(int i =0; i<number; i=i+2)
		{
			if(i<number-1)
			{
				while(a<C1[i].size() && b<C1[i+1].size())
				{
					if(C1[i].at(a) < C1[i+1].at(b))
					{
						a++;
						comparision++;
					}
					else
					{
						b++;
						comparision++;
					}
				
				}
				C2[k].resize(C1[i].size()+C1[i+1].size());
				merge(C1[i].begin(), C1[i].end(), C1[i+1].begin(), C1[i+1].end(), C2[k].begin());
				//cout<<C1[i].size()<<" "<<C1[i+1].size()<<" "<<C2[k].size()<<endl;
				k++;
				a=0;
				b=0;
			}
		}
		if(number%2 ==1)
		{ 
			C2[k].resize(C1[j-1].size());
			C2[k].assign(C1[j-1].begin(), C1[j-1].end());
		}
		//cout<<next<<endl;
		compall(C2, next);
		return;

  }
  void comptwo(vector<int> &C1, vector<int> &C2)
  {
 		int a =0;
		int b =0;
		while(a<C1.size() && b<C2.size())
		{
			if(C1.at(a) < C2.at(b))
			{
				a++;
				comparision++;
			}
			else
			{
				b++;
				comparision++;
			}
	}
	return;
 
  }
  //find kst smallest element (quickselect)
  int select4 (int A[], int start, int stop, int input)
  {
    int rank=input, x=input;
    // base cases
    if(start>=stop) // interval length is 0 or 1
    {
        rank=start;
        comparision++;
		  if(x>A[rank]) {rank++;}
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
      return rank;
    }
    // recursive case
    //cout<<"g "<<comparision<<" ";
    int pivotpos=partition(A,start,stop, &comparision, pivot_select);
    //if(comp++ && pivotpos==rank) return rank;
    //*comp = *comp +1;
	 if(pivotpos==rank) return rank;

	// *comp = *comp+1;
    if(rank<pivotpos) return select4(A, start,pivotpos-1,rank);
    else return select4(A, pivotpos+1,stop,rank);
    

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
