#ifndef _OFFLINE2
#define _OFFLINE2

#include "quicksort.h"
int pivot_select = -1;
int select_partition3 (int B[], int start, int end, int index,int *comp)
{
	int value = B[index];
	swap(B[index], B[end]);
	int store_index = start;
	for(int i = start; i<end; i++)
	{
		*comp = *comp+1;
		if(B[i] <=value)
		{
			swap(B[store_index], B[i]);
			store_index++;
		}
	}
	swap(B[end], B[store_index]);
	return store_index;
}
//find kst smallest element (quickselect)
int select3 (int A[], int start, int stop, int input, int *comp)
{
	/*if(start >= end || k<0) return start;
	//int pos=start + rand()%(end-start+1);

 	int mid=(start+end)/2;
	int pos = mid;

   //int newpivot = select_partition3(B, start, end, pos, comp);
	int newpivot = partition(B,start,end, comp, 1);

 	int pivotDist = newpivot-start+1;
	if(pivotDist == k) { return newpivot;}
	else if (k < pivotDist){ return select3 (B, start, newpivot-1, k, comp);}
	else { return select3(B, newpivot+1, end, k-pivotDist, comp);}*/

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
    int pivotpos=partition(A,start,stop, comp, pivot_select);
    //if(comp++ && pivotpos==rank) return rank;
    //*comp = *comp +1;
	 if(pivotpos==rank) return rank;

	// *comp = *comp+1;
    if(rank<pivotpos) return select3(A, start,pivotpos-1,rank,comp);
    else return select3(A, pivotpos+1,stop,rank,comp);
    

}	

void merge_comp(vector<int> &C1, vector<int> &C2 ,int *comp)
{
	int a =0;
	int b =0;
	while(a<C1.size() && b<C2.size())
	{
		if(C1.at(a) < C2.at(b))
		{
			a++;
			*comp = *comp+1;
		}
		else
		{
			b++;
			*comp = *comp+1;
		}
	}
	return;
}

void merge_comp2(vector<int> *C1, int j ,int *comp)
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
	/*int k = 0;

	for(int i =0; i<number; i=i+2)
	{
		if(i<number-1)
		{
			while(a<C1[i].size() && b<C1[i+1].size())
			{
				if(C1[i].at(a) < C1[i+1].at(b))
				{
					a++;
					*comp = *comp+1;
				}
				else
				{
					b++;
					*comp = *comp+1;
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
	merge_comp2(C2, next, comp);*/

	while(number >=2)
	{
		int one  = 0;
		int two = 0;
		for(int i = 0; i<number; i++)
			if(C1[i].size() < C1[one].size()) one = i;
		for(int i= 0; i<number; i++)
			if(i!=one && (two == one || C1[i].size() <C1[two].size())) two = i;
		merge_comp(C1[one], C1[two], comp);
		
		vector<int> temp1(C1[one].size()+C1[two].size());
		merge(C1[one].begin(), C1[one].end(), C1[two].begin(), C1[two].end(), temp1.begin());
		vector<int> temp2(C1[number-1].size());
		temp2.clear();
		temp2.assign(C1[number-1].begin(), C1[number-1].end());
					
		C1[one].clear();
		C1[one].assign(temp1.begin(), temp1.end());

		C1[two].clear();
		C1[two].assign(temp2.begin(), temp2.end());
		//cout<<C[i].size()<<" "<<C[k].size()<<endl;
		number--;
	}


	return;
}


void select_offline2 (vector<int> *C, int Q[], int queries, long single, int j, int *comp, int pivot)
{
	pivot_select = pivot;
	if(j==0 || queries<=0) return;
	//cout<<"start "<<queries<<" "<<j<<" "<<endl;

	long total = 0;
	long bound = single * single;
	//check total number of multiset elements is <=4*l^2 (bound)
	for(int i = 0; i<j ; i++)
	{
		total = total + C[i].size();
	}
	if(total <=bound)
	{
		if(j>0)
		{
			vector<int> sum_vector(total);
			/*merge_comp(C[0], C[1], comp);
			merge(C[0].begin(), C[0].end(), C[1].begin(), C[1].end(), sum_vector.begin());
			vector<int> tmp(total);
			
			for(int i=2; i<j; i++)
			{
				//vector<int> tmp(total);
				//tmp.clear();
				//tmp.assign(sum_vector.begin(), sum_vector.end());
				//sum_vector.clear();	
				
				//cout<<"finish?"<<endl;	
				merge_comp(tmp, C[i], comp);
				merge(C[i].begin(), C[i].end(), sum_vector.begin(), sum_vector.end(), tmp.begin());
				

				//sum_vector.swap(tmp);
			}*/
			merge_comp2(C, j, comp);

			for(int i=0; i<j; i++)
			{
				
				if(i==0)
				{
					sum_vector.assign(C[i].begin(), C[i].end());

				}
				else
				{
					vector<int> temp1(total);
					temp1.clear();
					//cout<<C[i].size()<<" "<<sum_vector.size()<<endl;
					//merge_comp(C[i], sum_vector, comp);
					merge(C[i].begin(), C[i].end(), sum_vector.begin(), sum_vector.end(), back_inserter(temp1));
				 	//cout<<C[i].size()<<" "<<sum_vector.size()<<" "<<temp1.size()<<endl;	
					sum_vector.clear();
					sum_vector.assign(temp1.begin(), temp1.end());
					
				}
			}
			//cout<<"result from "<<queries<<" : ";
			//for(int i =0; i<queries; i++) cout<<Q[i]<<" " <<sum_vector.at(Q[i])<<endl;
			
		}
		//else
		//	for(int i =0; i<queries; i++) cout<<Q[i]<<" " <<C[0].at(Q[i])<<endl;

		//cout<<"finish"<<endl;
		return;	
	}		
	//find invariant sequences and merge them
	for(int i =0 ; i<j-1; i++)
	{
		if(C[i].size() < single/2)
		{
			for(int k = i+1; k<j; k++)
			{
				if(C[k].size() == C[i].size())
				{
					//cout<<j<<" " <<k<< " "<<i<<endl;
					vector<int> temp1(C[k].size()+C[i].size());
					merge_comp(C[k], C[i], comp);
					merge(C[i].begin(), C[i].end(), C[k].begin(), C[k].end(), temp1.begin());
					//cout<<C[i].size()<<" "<<C[k].size()<<" "<<temp1.size()<<" "<<C[j-1].size()<<" "<<endl;	
					vector<int> temp2(C[k].size());
					temp2.clear();
					temp2.assign(C[j-1].begin(), C[j-1].end());
					
					C[i].clear();
					C[i].assign(temp1.begin(), temp1.end());

					C[k].clear();
					C[k].assign(temp2.begin(), temp2.end());
					//cout<<C[i].size()<<" "<<C[k].size()<<endl;
					//temp1.swap(C[i]);
					//C[j-1].swap(C[k]);
					j--;
					if(C[i].size() >=single/2) break;
				}
			}
		}
	}	
		
	//find median of medians
	int *median_array;
	int median_index = 0;
	median_array = new int[j];
	for(int i =0; i<j; i++) median_array[i] = C[i].at(C[i].size()/2);	
	
	/*median_index = select3 (median_array, 0, j-1, j/2, comp);
	int stand = median_array[median_index];
	*/
   
	int stand = return_index (median_array, 0, j-1, comp, 2);

	//split
 	vector<int> *C1;
	vector<int> *C2;
  	C1 = new vector<int>[j];
	C2 = new vector<int>[j];
	int num_c1 = 0;
	int num_c2 = 0;
	
	int *Q1;
	int	*Q2;

	Q1 = new int[queries];
	Q2 = new int[queries];
	
	int num_q1 = 0;
	int num_q2 = 0;
	
	int tem1 = 0;
	int tem2 = 0;
	int qstand = 0;
	int total1 = 0;
	int total2 = 0;	
	
	for(int i =0; i<j; i++)
	{
		for(int k =0; k<C[i].size(); k++)
		{
			if(C[i].at(k) <=stand)
			{
				C1[num_c1].push_back(C[i].at(k));
				tem1++;
				total1++;
				qstand++;
				*comp = *comp+1;
			}
			else
			{
				C2[num_c2].push_back(C[i].at(k));
				tem2++;
				total2++;
				*comp = *comp + 1;
			}	
		}
		//*comp = *comp + (int)log(C[i].size())/log(2);
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
	for(int i =0; i<queries; i++)
	{
	//	*comp = *comp+1;
		if(Q[i] < qstand)
		{
		//	*comp = *comp+1;
			Q1[num_q1] = Q[i];
			//cout<<"q1 "<<Q1[num_q1]<<" ";
			num_q1++;
		}
		else
		{
			Q2[num_q2] = Q[i]-qstand;
			//cout<<"q2 "<<Q2[num_q2]<<" ";
			num_q2++;
		}
		//cout<<endl;
	}
	//cout<<"stand "<<stand<<" "<<qstand<<" "<<num_q1<<" "<<num_q2<<endl;
	//cout<<"number " <<total1<<" "<<total2<<" "<<endl;

	//cout<<"left ";
	/*for(int i = 0; i<num_c1; i++) 
	{
		for(int j = 0; j<C1[i].size(); j++) cout<<C1[i].at(j)<<" ";
	}
	cout<<endl;

	cout<<"right ";
	for(int i = 0; i<num_c2; i++) 
	{
		for(int j = 0; j<C2[i].size(); j++) cout<<C2[i].at(j)<<" ";
	}
	cout<<endl;*/


	//call recursively
	//if(num_q1 > 0)
	select_offline2 (C1, Q1, num_q1, single, num_c1, comp, pivot);
	//if(num_q2 >0)
	select_offline2 (C2, Q2, num_q2, single, num_c2, comp, pivot);
	
}
#endif	
