
using namespace std;

#include<math.h>
#include<vector>
#include<algorithm>
#include "online.h"
#include "online2.h"
#include "online3.h"
#include "Timer.h"
#include "offline1.h"
#include "offline2.h"
#include <stdio.h>
#include <time.h>
#include <cmath>
#include <random>
#include <iostream>
//#include "mergesort.h"
int  comparision=0;
int comparision2=0;

int comp_quick = 0;
int comp_merge = 0;
int comp_on = 0;
int comp_on2 = 0;
int comp_on3 = 0;
int comp_of1 =0;
int comp_of2 = 0;
void mergeSort(int numbers[], int temp[], int array_size, int *comp);
void m_sort(int numbers[], int temp[], int left, int right, int *comp);
void merge(int numbers[], int temp[], int left, int mid, int right, int *comp);
void mergesort(int A[], int size, int *comp);
/*void shuffle(int A[], int size)
void swap2(int &x, int &y)
{
  int t; t=x; x=y; y=t;
}

void shuffle(int A[], int size)
{

	for(int i=start; i<(end-start+1)/2; i++)
	{
		
	}
}*/

double gaussianRandom(double average, double stdev) {
  double v1, v2, s, temp;

    do {
	     v1 =  2 * ((double) rand() / RAND_MAX) - 1;      
		 v2 =  2 * ((double) rand() / RAND_MAX) - 1;      
		 s = v1 * v1 + v2 * v2;
	} while (s >= 1 || s == 0);

	s = sqrt( (-2 * log(s)) / s );

	temp = v1 * s;
	temp = (stdev * temp) + average;

	return temp;
}
void mergesort(int A[], int size, int *comp)
{
	int *temp = new int[size];
	mergeSort(A, temp, size, comp);
}
void mergeSort(int numbers[], int temp[], int array_size, int *comp)
{
  m_sort(numbers, temp, 0, array_size - 1, comp);
}
 
 
void m_sort(int numbers[], int temp[], int left, int right, int *comp)
{
  int mid;
 
  if (right > left)
  {
    mid = (right + left) / 2;
    m_sort(numbers, temp, left, mid, comp);
    m_sort(numbers, temp, mid+1, right, comp);
 
    merge(numbers, temp, left, mid+1, right, comp);
  }
}
 
void merge(int numbers[], int temp[], int left, int mid, int right, int *comp)
{
  int i, left_end, num_elements, tmp_pos;
 
  left_end = mid - 1;
  tmp_pos = left;
  num_elements = right - left + 1;
 
  while ((left <= left_end) && (mid <= right))
  {
    if (numbers[left] <= numbers[mid])
    {
      *comp = *comp+1;
      temp[tmp_pos] = numbers[left];
      tmp_pos = tmp_pos + 1;
      left = left +1;
    }
    else
    {
      *comp = *comp+1;
      temp[tmp_pos] = numbers[mid];
      tmp_pos = tmp_pos + 1;
      mid = mid + 1;
    }
  }
 
  while (left <= left_end)
  {
    temp[tmp_pos] = numbers[left];
    left = left + 1;
    tmp_pos = tmp_pos + 1;
  }
  while (mid <= right)
  {
    temp[tmp_pos] = numbers[mid];
    mid = mid + 1;
    tmp_pos = tmp_pos + 1;
  }
 
  for (i=0; i <= num_elements; i++)
  {
    numbers[right] = temp[right];
    right = right - 1;
  }
}

int main()
{
	srand(time(NULL));
/*#include "config.h"
  
  FILE *fi = fopen("array.txt", "r");
  for(int i=0; i<Alen; i++)
  {
  	  fscanf(fi, "%d", &A[0][i]);
  }
  fclose(fi);
  for(int i=0; i<Alen; i++) 
  {
    A2[i]=A[0][i];
    //A3[i]=A[0][i];
  }
  
  for(int j = 1; j<count; j++)
  { 
  	for(int i=0; i<Alen; i++) A[j][i]=A[0][i];
  }
*/
	int Alen =(int)pow(2,20);// (int)pow(2,16);
	//int Alen = 50000;
	int count =7;
	int **A;
	A = new int*[count];
	int *A2 = new int[Alen]; 
	int *A3 = new int[Alen];
	for(int i=0; i<count; i++) A[i] = new int[Alen];  	 
	for(int i=0; i<Alen; i++) A3[i] = i;  	

	for(int i=0; i<Alen; i++) A[0][i]=Alen-i;
	int se = 0;
	/*for(int i =0; i<Alen; i++)
	{
		int rn = rand()%(Alen-se);
		A[0][i] = A3[rn];	
		int temp3 = A3[Alen-1-se];
		A3[rn] = temp3; 
		se++;
	}*/

	for(int i=0; i<Alen; i++) 
	{

		A2[i]=A[0][i];
	}
	
	for(int j = 1; j<count; j++)
	{ 
		for(int i=0; i<Alen; i++) A[j][i]=A[0][i];
	}
 FILE *fi = fopen("array.txt", "r");
  for(int i=0; i<Alen; i++)
  {
  	  fscanf(fi, "%d", &A[0][i]);
  }
  fclose(fi);
  for(int i=0; i<Alen; i++) 
  {
    A2[i]=A[0][i];
    //A3[i]=A[0][i];
  }
  
  for(int j = 1; j<count; j++)
  { 
  	for(int i=0; i<Alen; i++) A[j][i]=A[0][i];
  }

 	for(int u = (int)pow(2, 1); u<(int)pow(2,17); u=u*2)
	{
	for(int pp = 2; pp<=2; pp++){ 

	//for(int Alen = 30000 ; Alen<1000000; Alen = Alen+1000000)
	//{
	  /*int **A;
	  A = new int*[count];
	  int *A2 = new int[Alen]; 
	  int *A3 = new int[Alen];
	  for(int i=0; i<count; i++) A[i] = new int[Alen];  	
	  for(int i=0; i<Alen; i++) A3[i] = i;  	

	  for(int i=0; i<Alen; i++) A[0][i]=Alen-i;
	  
	  int se = 0;
	  for(int i =0; i<Alen; i++)
	  {
		int rn = rand()%(Alen-se);
		A[0][i] = A3[rn];	
		int temp3 = A3[Alen-1-se];
		A3[rn] = temp3; 
		se++;
	  }
	  for(int i=0; i<Alen; i++) 
	  {
		A2[i]=A[0][i];
	  }
	  for(int j = 1; j<count; j++)
	  { 
		for(int i=0; i<Alen; i++) A[j][i]=A[0][i];
	  }
	*/
	  //int u =32;
	  //int qnum = /*4;*/Alen/u+1;
	  int qnum = Alen/u+1;
	  //int u = 32;
	  int *q = new int[qnum];
	  /*int *q2 = new int[qnum];
	  int *q3 = new int[qnum];
	  int *q4 = new int[qnum];
	 */ int *T = new int[Alen];

	  int m = 0;
	  /*for(int i =0; i<qnum; i++)*/for(int i=1; i<Alen; i=i+u)
	  {
		q[m] = i;//rand()%Alen;
		/*q2[m]= q[m];
		q3[m] =q[m];
		q4[m] = q[m];
		T[m] = q[m];*/
		m++;
	  }
	  int *plot = new int[11];

	  for(int i = 0; i<Alen; i++) T[i] =i;
	  int e=0;
	  /*for(int i =0; i<m; i++)
	  {
		int rn = rand()%(Alen-e);
		q[i] = T[rn];
		//cout<<RQS[i]<< " "<<QS[i]<<" "<<endl;
		int temp3 = T[Alen-1-e];
		T[rn] = temp3; 
		e++;
	  }*/
	  /*for(int i =0; i<m; i++)
	  {

	  	q[i] = (int)((gaussianRandom(Alen/2, Alen/4)));
		if(q[i]<=0 || q[i] >= Alen){i--; continue;}
		plot[q[i]/100000]++;
		 //cout<<q[i]<<endl;
	  }*/
	  //for(int i = 0; i<11; i++) cout<<plot[i]<<"\t";

	  double const exp_dist_mean   = Alen/4;
	  double const exp_dist_lambda = 4 / exp_dist_mean;

	  /*std::random_device rd; 
	  std::exponential_distribution<> rng (exp_dist_lambda);
	  std::mt19937 rnd_gen (rd ());
	  for(int i =0; i<m; i++)
	  {
	 	 q[i] = Alen+1*(int)rng (rnd_gen);
		 //cout<<q[i]<<endl;
		 if(q[i]<=0 || q[i] >= Alen){i--; continue;}
		 plot[q[i]/100000]++;

		 //cout<<q[i]<<endl;
	  }*/
	  
	  //for(int i = 0; i<11; i++) cout<<plot[i]<<"\t";


	  int pivot_policy = pp;
	 //if(pp == 0)
	 cout << "Alen=" << Alen << "  #queries=" <<m<<endl;
	 #include "quicksort.h" 
	  quicksort(q, m, &e, 3);

	  //for(int i =0; i<qnum; i++) cout<<q[i]<<" ";
	  long double entropy = 0;

	  for(int i =0; i<=m; i++)
	  {
			if((i==0 && q[0] == 0) || (i > 0 && i<m && q[i] == q[i-1]) || (i == m && Alen == q[i-1])  ) 
			   entropy = entropy + 0;
			else if(i== 0 && q[0] != 0)
				entropy = entropy +  q[i]*(log((double)Alen/q[i])/log(2));
			else if (i == m)
			   entropy = entropy + (Alen-q[i-1])*(log((double)Alen/(Alen-q[i-1]))/log(2));
			else
			   entropy = entropy + (q[i]-q[i-1])*(log((double)Alen/(q[i]-q[i-1]))/log(2));
	  } 

	  	  
	  if(u==2)
	  {
		quicksort(A[0], Alen, &comp_quick, pivot_policy);
		//cout<<"Quick sort:      ";
		cout << comp_quick<<endl;
		mergesort(A[1], Alen, &comp_merge);
		//cout<<"Merge sort:      ";
		cout<<comp_merge<<endl;
	  }
	  
	  //if(pp == 0)
	  cout<<entropy<<endl;
	  //cout<<"Online(sorted):   ";
	  int repeat =1;
	  int total = 0;
	  if(pp ==1) repeat = 10;
	  for(int gg = 0; gg<repeat ; gg++)
	  {
	  	online *x = new online(A[2],Alen, pivot_policy);
	  	x->setcomp(1);
	  	for(int i=0; i<m; i++)
			 x->select(q[i]);
	  	//cout << x->comp()-1<<endl;
		total = total + x->comp()-1;
	  	//cout<<x->sel()<<endl;
		delete x;
	  }
	  cout<<total/repeat<<endl;
	  //cout<<"Online2           "
	  online2 *z = new online2(A[3],Alen, pivot_policy);
	  z->setcomp(1);
	  for(int i=0; i<m; i++)
	 { z->select(q[i]); }
	  cout << z->comp()-1<<endl;  
	 
	 delete z;
	long l = 1; 

	  //cout<<"Online3           ";
	  /*online3 *w = new online3(A[4], Alen, pivot_policy);
	  w->setcomp(1);
	  long double cur_entropy = 0;
	  	  for(int i=0; i<m; i++)
	  {
		  cur_entropy=0;
		  for(int j =0; j<=i; j++)
		  {
			if((j==0 && q[0] == 0) || (j > 0 && j<m && q[j] == q[j-1]) || (j == m && Alen == q[j-1])  ) 
			   cur_entropy = cur_entropy + 0;
			  else if(j== 0 && q[0] != 0)
			  cur_entropy = cur_entropy +  q[j]*(log((double)Alen/q[j])/log(2));
			  else if (j == m-1)
			   cur_entropy = cur_entropy + (Alen-q[j])*(log((double)Alen/(Alen-q[j]))/log(2));
			else
			   cur_entropy = cur_entropy + (q[j+1]-q[j])*(log((double)Alen/(q[j+1]-q[j]))/log(2));

			} 
			if(cur_entropy ==0 ) cur_entropy = 1;
			long new_l = 1;
			//if(l < (log(cur_entropy/(double)Alen)/log(2)))
			//{
				new_l = (long)(log(cur_entropy/(double)Alen)/log(2))+1;
			//}
		   if(new_l >= l)
			{
				l = l*2;
			}
			//cout<<" query value "<<q[i]<<" l : "<<l<<endl;	
			w->select(q[i], l);
			//cout<<q[i]<<" "<<l<<" "<<w->comp()-1<<endl;
	  }
	  cout<< w->comp()-1<<endl;

	  delete w;*/
	  //for(int i =0; i<m; i++) cout<<q[i] << " ";
	  //cout<<endl;
	  //cout<<"offline1(Sorted): ";
	  select_offline1 (A[5], q, 0, m-1, 0, Alen, Alen/2, &comparision, pivot_policy);
	  //cout << t.elapsed() << endl;
	  cout <<comparision<<endl;  

	  //cout<<"offline2(Sorted): ";
	  l = 1;
	  //set the l
	  //long l = 1;
	  if(l < (log(entropy/(double)Alen)/log(2)))
	  {
		l = (long)(log(entropy/(double)Alen)/log(2))+1;
	  }
	  //cout<<l<<endl;
	  long single = 2*l;
	  int number = (int)Alen/single+1;
	  vector<int> *C;

	  //split the original sequence
	  C = new vector<int>[number];  
	  
	  int zz = 0;
	  for(int i=0; i<Alen; i++)
	  {
		if(i!=0 && i%single == 0) zz++;
		C[zz].push_back(A[6][i]);   
	  }

	  //sort the collection of sequences
	  for(int k =0; k<=zz ; k++)
	  {
		int *arr;
		arr = new int[single];
		std::copy(C[k].begin(), C[k].end(), arr);
		//cout<<C[k].size();
		//quicksort(arr, C[k].size(), &comparision2, pivot_policy);
		 mergesort(arr, C[k].size(), &comparision2);
		 sort(C[k].begin(), C[k].end());
		//delete []arr;
	  }

	  //do offline2
	  //cout<<l<<endl;
	  select_offline2 (C, q, m, single, zz+1, &comparision2, pivot_policy);
	  

	  //cout << t.elapsed() << endl;
	  cout <<comparision2<<endl; 
	  for(int i =0 ; i<number; i++)
	  {
			vector<int>().swap(C[i]); 
	  }
	 delete []C;
	  for(int i =0; i<count; i++)
	  {
		for(int j=0; j<Alen; j++) A[i][j] = A2[j];
	  }

	  /*for(int i =0; i<count; i++)
	  {
		//for(int j=0; j<Alen; j++) A[i][j] = A2[j];
		delete []A[i];
	  }
	  delete []A;
	  delete []A2;
	  */
	  cout<<endl;
	  comp_quick = 0;
	  comparision = 0;
	  comparision2 = 0;
	  delete []q;
	  delete []T;
	  /*for(int k =0; k<=zz; k++)
	  {
		  C[k].clear();
	  }*/
	  /*delete q2;
	  delete q3;
	  delete q4;
	  delete T;*/
	  //delete *y;
	}
}


  return 0;
  /*for(int i=0; i<queries; i++)
  {

     if(i%2==0) // do selection query
     {
       int rank=rand()%Alen;
       cout << i+1 << ": ["<< rank << "] "<< x.select(rank) << endl;
     }
     else // do rank/search query
     {
       int value=rand()%1000;
       cout << i+1 << ": "<< value << " ["<< x.rank(value) <<"]\n";;
     }

     for(int j=0; j<Alen; j++) 
       cout << A[j] << (j%20==19?'\n':' ');

     x.print(cout);
  }*/
/*
 */
/*
  // loop to sort
  for(int j=2; j<Alen; j+=2) x.select(j);
  x.print(cout);
*/

  //delete [] A;
  //return 0;
}
