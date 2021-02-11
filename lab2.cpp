/*

Chloe VanCory
COSC 320 
Lab2

Goals: Quicksort, partition function and swap. Mergesort with the merge function

valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes ./main look

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


void makeArrRandom(int * arr, int length);
void makeArrSorted(int * arr,int length);
void makeArrBackward(int * arr,int length);
void makeArrDuplicates(int * arr,int length);

void arrCopy(int* source , int * dest, int length);


void swap(int & num1, int& num2);
int partition(int* arr, int start, int end, long &numSwaps); // big O n
void quicksort(int* arr,int start,int end, long & numSwaps);

int * merge(int * arr1, int * arr2, int length1, int length2, long & numCompared);
int * mergesort(int * arr, int start, int end,long & numCompared);


void timeMergesort( int * arr, int start, int end, long & numCompared);
void timeQuicksort( int * arr, int start, int end, long & numSwaps);


















int main(){

    // cout<<"This program begins with arrays of length 10,0000 and increments by 10,0000 when you start"<<endl;
    // sleep(5);
    srand(time(NULL));
    int length=4;
    int start_position=0;
    long numSwaps=0;
    long numCompared;

   
    int * arrRan1= new int [length];
    int * arrRan2= new int [length];

    makeArrRandom(arrRan1,length);
    arrCopy(arrRan1,arrRan2,length);

    timeMergesort(arrRan1, start_position, length,numCompared);
    timeQuicksort(arrRan2,start_position,length, numSwaps);


    int * arrSort1= new int [length];
    int * arrSort2= new int [length];
    makeArrSorted(arrSort1,length);
    arrCopy(arrSort1,arrSort2,length);

    timeMergesort(arrSort1, start_position, length,numCompared);
    timeQuicksort(arrSort2,start_position,length, numSwaps);


    int * arrBackward1 = new int [length];
    int * arrBackward2 = new int [length];
    makeArrBackward(arrBackward1,length );
    arrCopy(arrBackward1,arrBackward2,length );

    timeMergesort(arrBackward1, start_position, length,numCompared);
    timeQuicksort(arrBackward2,start_position,length, numSwaps);
    



    int * makeArrDuplicates1= new int [length];
    int * makeArrDuplicates2= new int [length];
    makeArrSorted(makeArrDuplicates1,length);
    arrCopy(makeArrDuplicates1, makeArrDuplicates2,length);

    timeMergesort(makeArrDuplicates1, start_position, length,numCompared);
    timeQuicksort(makeArrDuplicates2,start_position,length, numSwaps);
    






    delete[] arrRan1;
    delete[] arrRan2;
    delete [] arrBackward1;
    delete [] arrBackward2;
    delete [] arrSort1;
    delete [] arrSort2;
    delete [] makeArrDuplicates1;
    delete [] makeArrDuplicates2;

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
            // printArray(arr,n);
        }
    }
    return true;

}


void makeArrRandom(int * arr, int length){

    for(int i=0;i<length;i++){
        arr[i]= rand() % 1000+ 2; 
    }

    //     puts("CHLOES CUSTOM ARRAY");  // used for when to hard code input
    // for(int i=0;i<length;i++){ 
    //     int num;
    //     cin>> num;
    //     arr[i]= num; 
    // }
     
}

void makeArrSorted(int * arr ,int length){
     for(int i=0;i<length;i++){
         arr[i]=i;
     }

}

void makeArrBackward(int * arr,int length){
    int backwards=length;
     for(int i=0;i<length;i++){
         arr[i]= backwards;
         backwards--;
     }
}

// creates an array where half of the numbers are 30 and the other half are random
void makeArrDuplicates(int * arr,int length){
    for(int i=0;i<length;i++){
        if(i%2 == 0){
            arr[i]=30;
        }else{
             arr[i]= rand() % 1000+ 1;
        }
        
    }
}



void arrCopy(int* source , int * dest, int length){
    
    for(int i=0;i<length;i++){
        dest[i]= source[i];
    }



}



void swap(int & num1, int& num2){
    // <<"start  SWAP : num1="<<num1<<" "<<num2<<endl;

    int temp1=num1;
    int temp2=num2;
    num1= temp2;
    num2=temp1;

    // <<"END OF SWAP : num1="<<num1<<" "<<num2<<endl;
    

}


int partition(int* arr, int start, int end, long & numSwaps){
    int pivot = arr[end-1];
    int loc = start-1;
   

    // // puts("pivot and loc");
     //cout<<pivot<<" "<< loc<<endl;

    for( int i= start; i < end-1; i++){
        // // cout<<"i="<<i<<endl;
        if(arr[i] <= pivot){
            // // cout<<" enter swap \n"<<endl;
            loc = loc +1;
            swap(arr[loc], arr[i]);
            numSwaps++;
        }
    }
    // cout<<"final swap arr[loc+1]= "<< arr[loc+1]<<" arr[end-1]="<< arr[end-1]<<endl;
    swap(arr[loc+1], arr[end-1]);
    return loc+1;
}

void quicksort(int* arr,int start,int end, long & numSwaps){
    // printArray(arr,end);
    // sleep(2);

    if(start< end){
        int pivot= partition(arr,start,end, numSwaps);

        quicksort(arr,start,pivot, numSwaps);
        quicksort(arr,pivot+1,end, numSwaps);

    }
    // puts("sorted arr");
    // printArray(arr,end);



}


int* merge(int * arr1, int * arr2, int length1, int length2, long & numCompared){
    // cout<<"MERGE"<<endl;
    // cout<<"arr1Lenth= "<<length1<<" length2= "<<length2<<endl;

        // cout<<"merge arr1= ";
        // printArray(arr1,length1);
        // cout<<" merge arr2= ";
        // printArray(arr2, length2);


    int position1=0;// keeps track of the indexes
    int position2=0;

    int * arr3 = new int[ length1 + length2];
    int front= 0; // keeps track of "front" of arr2

    while(position1 < length1 && position2 < length2){
        // sleep(2);
        // cout<<"here"<<endl;

        if( arr1[position1] <= arr2[position2] ){
            arr3[ front++ ] = arr1[ position1++ ]; // increments both after using 
            // cout<<"enter first"<<endl; 
            
        }else if( arr1[position1] > arr2[position2] ){
            arr3[ front++ ] = arr2[ position2++ ]; // increments both after using 
            // cout<<"enter second"<<endl; 

        }
        numCompared++;

       
    }
    //  printArray(arr3,length1+ length2);
    // takes care of the case where oen side is completely sorted and " short circuits" the above
    // while loop
    while(position1 < length1){
        arr3[ front++ ] = arr1[ position1++ ]; // increments both after using 
        // cout<<"in while loop 2 arr3= "<<endl; 
        // printArray(arr3,length1+ length2);
        numCompared++;

    }

    while(position2< length2){
        arr3[ front++ ] = arr2[ position2++ ]; // increments both after using 
        // cout<<"in while loop 3 arr3= "<<endl; 
        // printArray(arr3,length1+ length2);
        numCompared++;

    }

    // cout<<"         FINAL ARR in merge function"<<endl; 
        // printArray(arr3,length1+ length2);

    delete arr1;
    delete arr2;


    return arr3;





}


int * mergesort(int * arr, int start, int end, long& numCompared){
        // cout<<" \nEnter MERGESORT start = "<<start <<" end= "<<end<<endl;
        // sleep(1);
        // printArray(arr, end);
         int mid = (start + end )/ 2;

    if(mid!=0){// arr is not empty
    // if(start< end){
       
        // cout<<" mid= "<<mid<<endl;

        int * arr2= new int[ mid-start ];
        int * arr3= new int[ end-mid ];


        int j=0,k=0;
        for(int i= 0 ; i< end; i++){

            if(i<mid){
               arr2[j++] = arr[i];
                // puts("first");
                // cout<<i<<endl;
            }else if (i>=mid ){
               arr3[k++] = arr[i];
                // puts("sec");
                // cout<<i<<endl;


            }   
            
        }


        // cout<<"arr2= ";
        // printArray(arr2, mid-start);
        // cout<<"arr3= " ;
        // printArray(arr3, end-mid );

        // cout<<"mid-start= "<<mid-start<<" end-mid= "<<end-mid<<endl;

        arr2 = mergesort(arr2 , start , mid-start,numCompared);
        arr3 = mergesort(arr3 , start , end-mid, numCompared);

        // cout<<"mid-start= "<<mid-start<<" end-mid= "<<end-mid<<endl;
        // puts("end of merge sort");

        delete arr;
        return merge( arr2, arr3, mid-start , end-mid, numCompared);

        delete [] arr2;
        delete [] arr3;

     } else{
        // puts("ELSE");
       


        return arr;
    }

 
    
}


void timeMergesort( int * arr, int start, int end, long& numCompared){
   puts("Entering Mergesort");

 
  auto begin = std::chrono::system_clock::now();
   mergesort(arr, start, end, numCompared );


  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)

    << "elapsed time: " << elapsed_seconds.count() << " seconds";

    if(isSorted(arr,end)==true){
        cout<<"\nThe number of swaps for mergesort was "<< numCompared<<"\n"<<endl;
        numCompared=0;
    }else {
         cout<<"NOT SORTED  "<< numCompared<<"\n"<<endl;

    }

    
}

void timeQuicksort( int * arr, int start, int end, long &numSwaps){
   puts("Entering Quicksort");
 
  auto begin = std::chrono::system_clock::now();
  quicksort(arr, start, end , numSwaps);


  auto finish = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = finish-begin;
  std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
  std::cout << " finished at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << " seconds";

    if(isSorted(arr,end)==true){
        cout<<"\nThe number of swaps for QuickSort was "<< numSwaps<<"\n"<<endl;
        numSwaps=0;

    }else {
         cout<<"NOT SORTED  "<< numSwaps<<"\n"<<endl;

    }

    
}

