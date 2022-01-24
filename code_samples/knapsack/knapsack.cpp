#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <sstream>
#include <string>


using namespace std;

int vessel_cap = 1000;
int number_items = 1000;

int BLOCK = 1000;
int AVAILTHREAD = 8;

int* value;
int* weight;


void looprun(int **itemsjo) {

  int mainLB;

  for (int K = 1; K <= number_items; K = K + AVAILTHREAD) { 
    
#ifdef DEBUG
    printf("Starting next group of items ...\n");
#endif 
    /* preloop */
    for (int t = K, i = 1; t < K + AVAILTHREAD; t++, i++) {
#ifdef DEBUG
      if (AVAILTHREAD - i != 0)
	printf("Item = %d\tBlock : 1:%d\n", t, BLOCK * (AVAILTHREAD - i));
#endif
      for (int xx = 1; xx <= BLOCK * (AVAILTHREAD - i); xx++) {
	if(xx < weight[t])
	  itemsjo[t][xx]=itemsjo[t-1][xx];
	else {
	  int temp1 = itemsjo[t-1][xx];
	  int temp2 = itemsjo[t][xx - weight[t]] + value[t];
	  
	  if (temp1 > temp2)
	    itemsjo[t][xx]= temp1;
	  else 
	    itemsjo[t][xx]= temp2;
	}
      }
    }
    

    /* main loop */
    mainLB =  BLOCK * (AVAILTHREAD - 1) + 1;
    for (int x = mainLB; x <= vessel_cap; x = x + BLOCK) {
#ifdef DEBUG
      printf("\n*** Spawning ***\n");
#endif
      //      omp_set_num_threads(AVAILTHREAD);
      //#pragma omp parallel for
      for (int t = 1; t <= AVAILTHREAD; t++) {
#ifdef DEBUG	
	printf("Item = %d\tBlock : %d:%d\n", t + (K - 1), x - ((t - 1) * BLOCK), (x - ((t - 1) * BLOCK) + BLOCK - 1));
#endif
	int m, result, jopt, mopt;
	int innerLB = x - ((t - 1) * BLOCK);

	for (int xx=innerLB; (xx < vessel_cap) && (xx < innerLB + BLOCK); xx++) {
	  if(xx < weight[t + (K - 1)])
	    itemsjo[t + (K - 1)][xx]=itemsjo[t + (K - 1) - 1][xx];
	  else {
	    int temp1 = itemsjo[t + (K - 1) - 1][xx];
	    int temp2 = itemsjo[t + (K - 1)][xx - weight[t + (K - 1)]] + value[t + (K - 1)];
	    if (temp1 > temp2)
	      itemsjo[t + (K - 1)][xx]= temp1;
	    else 
	      itemsjo[t + (K - 1)][xx]= temp2;
	  }
	}
      }
#ifdef DEBUG
      printf("*** Synchronizing ***\n");
#endif
    }

    
    /* post loop */
    for (int t = K, i = 1; t <  K + AVAILTHREAD; t++, i++) {
      for (int xx = (vessel_cap - (BLOCK * i)) + 1; xx <= vessel_cap; xx++) {
	  if( xx < weight[t])
	    itemsjo[t][xx]=itemsjo[t-1][xx];
	  else {
	    int temp1 = itemsjo[t-1][xx];
	    int temp2 = itemsjo[t][xx - weight[t]] + value[t];
	    
	    if (temp1 > temp2)
	      itemsjo[t][xx]= temp1;
	    else 
	      itemsjo[t][xx]= temp2;
	  }
      }
    }

  }
}

int solution(int c, int **itemsjo) {

  ::ofstream out("s3solution.dat", ios::app);

  if (!out) {
    cerr << "Results file could not be opened" << endl;
    return 1;
  }
  
  out << "Capacity: "<< c << endl;
  int itemcount = 0;  
  int x = c;
  int k = number_items;
  while (k >= 1 && x >=0) {  
      int m, result, jopt, mopt;
      
      jopt = INT_MIN;
      mopt = INT_MAX;
      m=0;
      int temp1=itemsjo[k-1][x];
      int temp2=-1000;
      if(x >= weight[k]) {
	temp2 = itemsjo[k][x - weight[k]] + value[k];
      }
      
      if (k==1 && x==0) {
	if(itemcount > 0) {  					
	  out <<"Item "<<k<<" Put "<<itemcount<<" units "<<endl ;
	}
	k=k-1;
      }
      else if (temp1 > temp2) {
	if(itemcount > 0) {  					
	  out <<"Item "<<k<<" Put "<<itemcount<<" units "<<endl ;
	}
	k=k-1;
	itemcount=0;
      }
      else {
	x= x -weight[k];   
	itemcount++;
      }
  }
  out << endl << endl;
  out.close();
  return 0;
}


int main(int argc, char* argv[]) {

  int i;
  int w, v;
	
#ifdef DEBUG
  for(int i = 0; i < argc; i++)
    cout << "argv[" << i << "] = " << argv[i] << endl; 
#endif 
	  
  ::ifstream data(argv[1], ios::in);
  if (!data) {
    cerr <<"Data file could not be opened"<<endl;
    return 1;
  }

  data >> number_items >> vessel_cap;
  
  
  cout << "Items: " << number_items << "   Capacity: "<< vessel_cap << endl << endl;
   
  double iostart_time1, iorun_time1,lstart_time,lrun_time,iostart_time2,iorun_time2;
   
  int** itemsjo;
  itemsjo=new int*[number_items+1];
   
  for(int i = 0; i < number_items+1; i++) {
    itemsjo[i]=new int[vessel_cap+1];
    
    for(int j=0 ; j < vessel_cap+1 ; j++) {
      itemsjo[i][j] = 0;
    }
  }
  
  value = new int[number_items+1];
  weight = new int[number_items+1];
  
  for(int i = 0; i < number_items+1; i++) {
    value[i] = 0;
    weight[i] = 0;
  }

  i = 1;
  while (i <= number_items) {
    data >> w >> v;
    weight[i]=w;
    value[i]=v;
    i++;
  }
  data.close();


  looprun(itemsjo);
	
	

  ::ofstream results("results.dat", ios::out);
  if (!results) {
    cerr<<"Results file could not be opened"<<endl;
    return 1;
  }
	
  for (int x=0; x<=vessel_cap; x++) {	
    results<< x << "  " <<itemsjo[number_items][x]<<endl;
  }	
  cout<< "Results for different vessel capacities " 
      << "were saved in file results.dat " <<endl<<endl;
  
  cout<<endl;
	
  results.close();
  
	
  double sstart_time,sstime;
  
  int c = 10000;
  
  return 0;
}
