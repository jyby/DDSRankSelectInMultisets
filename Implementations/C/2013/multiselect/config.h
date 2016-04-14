  //#include <stdio.h>
  //using namespace std;
  //#include <cmath>
  const int queries=5000;
  const int Alen=30000;//(int)pow(queries,1.5);
  int count = 7;
  int **A;
  A = new int*[count];
  for(int i=0; i<count; i++) A[i] = new int[Alen];  	
  
  //int *A[4]=new int[4][Alen];
  int *A2 = new int[Alen];
  int *A3 = new int[Alen];
  
    
  
  /*int **Q;
  Q = new int*[count];
  for(int i=0; i<count; i++) Q[i] = new int[queries];  	  
  
  int *Q2 = new int[queries];
  int *Q3 = new int[queries];
*/
  srand(0);
 
  for(int i=0; i<Alen; i++) A3[i]=i;
  //for(int i=0; i<Alen; i++) A[0][i]=Alen-i;
  //for(int i=0; i<queries; i++) Q[0][i]=rand()%Alen;
  int se = 0;
  for(int i =0; i<Alen; i++)
  {
	int rn = rand()%(Alen-se);
	A[0][i] = A3[rn];	
	//cout<<RQS[i]<< " "<<QS[i]<<" "<<endl;
	int temp3 = A3[Alen-1-se];
	A3[rn] = temp3; 
	se++;
  }
  for(int i=0; i<Alen; i++) 
  {
    A2[i]=A[0][i];
    //A3[i]=A[0][i];
  }
  
  for(int j = 1; j<count; j++)
  { 
  	for(int i=0; i<Alen; i++) A[j][i]=A[0][i];
  }
  /*for(int i=0; i<queries; i++)
  { 
     Q2[i]=Q[0][i];
    Q3[i]=Q[0][i];
  }
  for(int j = 1; j<4; j++)
  {
  	for(int i=0; i<queries; i++) Q[j][i]=Q[0][i];
  }
*/
  //assume that Q is sorted
  #include "quicksort.h"
  /*int temporary = 0;
  for(int j = 0; j<4; j++)
  	quicksort(Q[j], queries, &temporary, 0);


  quicksort(Q2, queries, &temporary, 0);
  quicksort(Q3, queries, &temporary, 0);


  //storting test

  int *QS = new int[Alen/2+1];
  int *RQS = new int[Alen/2+1];
  int *TQ = new int[Alen/2+1];
  int *QS2 = new int[Alen/2+1];
  int *QS3 = new int[Alen/2+1]; 
  
  int tt = 0;
  int nqs;
  
  for(int i =1; i<Alen; i=i+2)
  {
     QS[tt] = i;
     QS2[tt] = i;
     QS3[tt] = i;
     TQ[tt] = i;
     tt++;
  }

  if(Alen%2 == 0) 
  {
	nqs = Alen/2-1;
  }
  else
  {
 	nqs = Alen/2;
  }
  
  int se = 0;
  for(int i =0; i<nqs; i++)
  {
	int rn = rand()%(nqs-se);
	RQS[i] = TQ[rn];
	//cout<<RQS[i]<< " "<<QS[i]<<" "<<endl;
	int temp3 = TQ[nqs-1-se];
	TQ[rn] = temp3; 
	se++;
  }  
 */
  //cout << "Alen=" << Alen << "  #queries=" <<queries<<endl;
  //cout << "Alen=" << Alen << "  #queries=" <<nqs<<endl;

