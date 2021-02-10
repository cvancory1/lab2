/*

Chloe VanCory
COSC 320 
Lab2

Goals: Quicksort, partion function and swap. Mergesort with the merge function



*/


#include <iostream>
#include <stdio.h>
#include <chrono>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include<unistd.h>
using namespace std;

void printArray(int* A, int length);
bool isSorted(int* arr, int n);

int* makeArrRandom(int length);
int* makeArrSorted(int length);
int* makeArrBackward(int length);
int* makeArrDuplicates(int length);

int* arrCopy(int* A, int length);

void swap(int & num1, int& num2);
int partition(int* arr, int start, int end, long &numSwaps); // big O n
void quicksort(int* arr,int start,int end, long & numSwaps);

int * merge(int * arr1, int * arr2, int length1, int length2, long & numCompared);
int * mergesort(int * arr, int start, int end);


void timeMergesort( int * arr, int start, int end);
void timeQuicksort( int * arr, int start, int end,long & numSwaps);


















int main(){

    // cout<<"This program begins with arrays of length 10,0000 and increments by 10,0000 when you start"<<endl;
    // sleep(5);
    srand(time(NULL));
    int length=4;
    int start_position=0;
    long numSwaps=0;


    int * arrRan1= makeArrRandom(length);

    int * arrRan2= arrCopy(arrRan1, length);

    timeMergesort(arrRan1, start_position, length);
    timeQuicksort(arrRan2,start_position,length, numSwaps);




    // int * arr= new int [3];
    // int * arr1= new int [3];
    // for(int i=0;i<3;i++){
    //     cin>> arr[i];
    // }

    //  for(int i=0;i<3;i++){
    //     cin>> arr1[i];
    // }

    // merge(arr,arr1,3,3);





}























void printArray(int* A, int length){
    for(int i=0;i< length; i++){
        cout<< A[i]<<" ";
    }
    cout<<endl;
}

bool isSorted(int* arr, int n){

    for(int i=1;i<n;i++){
        if(arr[i-1]>arr[i]){
            return false;
            printArray(arr,n);
        }
    }
    return true;

}


int* makeArrRandom(int length){

    int *arr= new int[length];
    for(int i=0;i<length;i++){
        arr[i]= rand() % 1000+ 2; 
    }

    //     puts("CHLOES CUSTOM ARRAY");  // used for when to hard code input
    // for(int i=0;i<length;i++){ 
    //     int num;
    //     cin>> num;
    //     arr[i]= num; 
    // }
     
    return arr;
}

int* makeArrSorted(int length){
    int *arr= new int[length];
     for(int i=0;i<length;i++){
         arr[i]=i;
     }
     return arr;

}

int* makeArrBackward(int length){
    int *arr= new int[length];
    int backwards=length;
     for(int i=0;i<length;i++){
         arr[i]= backwards;
         backwards--;
     }
     return arr;
}

// creates an array where half of the numbers are 30 and the other half are random
int* makeArrDuplicates(int length){
    int *arr= new int[length];
    for(int i=0;i<length;i++){
        if(i%2 == 0){
            arr[i]=30;
        }else{
             arr[i]= rand() % 1000+ 1;
        }
        
    }
    return arr;
}



int* arrCopy(int* A, int length){
    int * arr= new int[length];
    
    for(int i=0;i<length;i++){
        arr[i]= A[i];
    }

    return arr;
}



void swap(int & num1, int& num2){
    cout<<"start  SWAP : num1="<<num1<<" "<<num2<<endl;

    int temp1=num1;
    int temp2=num2;
    num1= temp2;
    num2=temp1;

    cout<<"END OF SWAP : num1="<<num1<<" "<<num2<<endl;
    puts("");
    

}


int partition(int* arr, int start, int end, long & numSwaps){
    int pivot = arr[end-1];
    int loc = start-1;
   

    puts("pivot and loc");
    cout<<pivot<<" "<< loc<<endl;

    for( int i= start; i < end-1; i++){
        cout<<"i="<<i<<endl;
        if(arr[i] <= pivot){
            cout<<" enter swap \n"<<endl;
            loc = loc +1;
            swap(arr[loc], arr[i]);
            numSwaps++;
        }
    }
    cout<<"final swap arr[loc+1]= "<< arr[loc+1]<<" arr[end-1]="<< arr[end-1]<<endl;
    swap(arr[loc+1], arr[end-1]);
    return loc+1;
}

void quicksort(int* arr,int start,int end, long & numSwaps){
    printArray(arr,end);
    // sleep(2);

    if(start< end){
        int pivot= partition(arr,start,end, numSwaps);

        quicksort(arr,start,pivot, numSwaps);
        quicksort(arr,pivot+1,end, numSwaps);

    }
    puts("sorted arr");
    printArray(arr,end);


    if(isSorted(arr,end)==true){
        cout<<"\nThe number of swaps is "<< numSwaps<<"\n"<<endl;

    }else {
         cout<<"NOT SORTED  "<< numSwaps<<"\n"<<endl;

    }
    return;
}


int* merge(int * arr1, int * arr2, int length1, int length2, long & numCompared){
    cout<<"MERGE"<<endl;
    cout<<"arr1Lenth= "<<length1<<" length2= "<<length2<<endl;

        cout<<"merge arr1= ";
        printArray(arr1,length1);
        cout<<" merge arr2= ";
        printArray(arr2, length2);


    int position1=0;// keeps track of the indexes
    int position2=0;

    int * arr3 = new int[ length1 + length2];
    int front= 0; // keeps track of "front" of arr2

    while(position1 < length1 && position2 < length2){
        // sleep(2);
        // cout<<"here"<<endl;
        numCompared++;

        if( arr1[position1] <= arr2[position2] ){
            arr3[ front++ ] = arr1[ position1++ ]; // increments both after using 
            cout<<"enter first"<<endl; 


            
        }else if( arr1[position1] > arr2[position2] ){
            arr3[ front++ ] = arr2[ position2++ ]; // increments both after using 
            cout<<"enter second"<<endl; 

        }
       
    }
     printArray(arr3,length1+ length2);
    // takes care of the case where oen side is completely sorted and " short circuits" the above
    // while loop
    while(position1 < length1){
        arr3[ front++ ] = arr1[ position1++ ]; // increments both after using 
        cout<<"in while loop 2 arr3= "<<endl; 
        printArray(arr3,length1+ length2);
        numCompared++;

    }

    while(position2< length2){
        arr3[ front++ ] = arr2[ position2++ ]; // increments both after using 
        cout<<"in while loop 3 arr3= "<<endl; 
        printArray(arr3,length1+ length2);
        numCompared++;

    }

    cout<<"         FINAL ARR in merge function"<<endl; 
        printArray(arr3,length1+ length2);

    return arr3;





}


int * mergesort(int * arr, int start, int end){
        long numCompared;
        cout<<" \nEnter MERGESORT start = "<<start <<" end= "<<end<<endl;
        // sleep(1/2);
        printArray(arr, end);
         int mid = (start + end )/ 2;

    if(mid!=0){// arr is not empty
    // if(start< end){
       
        cout<<" mid= "<<mid<<endl;

        int * arr2= arrCopy ( arr, mid-start );
        int * arr3= new int[ end-mid ];

        int j=0;
        for(int i= mid ; i< end; i++){
            arr3[j++] = arr[i];
        }

        cout<<"arr2= ";
        printArray(arr2, mid-start);
        cout<<"arr3= " ;
        printArray(arr3, end-mid );
 
        cout<<"mid-start= "<<mid-start<<" end-mid= "<<end-mid<<endl;

        arr2 = mergesort(arr2 , start , mid-start);
        arr3 = mergesort(arr3 , start , end-mid);

          cout<<"mid-start= "<<mid-start<<" end-mid= "<<end-mid<<endl;

        puts("end of merge sort");
        // for shorter version 

        return merge( arr2, arr3, mid-start , end-mid, numCompared);

      

     } else{
        puts("ELSE");
        return arr;
    }

    puts("FINAL ARR");
    printArray(arr,end);

    if(isSorted(arr,end)==true){
        cout<<"\nThe number of swaps is "<< numCompared<<"\n"<<endl;

    }else {
         cout<<"NOT SORTED  "<< numCompared<<"\n"<<endl;

    }
    
}


void timeMergesort( int * arr, int start, int end){

 
  auto begin = std::chrono::system_clock::now();
  mergesort(arr, start, end );

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";

    
}

void timeQuicksort( int * arr, int start, int end, long &numSwaps){

 
  auto begin = std::chrono::system_clock::now();
  quicksort(arr, start, end , numSwaps);

  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds\n\n";

    
}