#include <iostream>
using namespace std ;

class Counting_inversion{
      public :
      int INVC;

      Counting_inversion(){
      	INVC=0;
      }

      int INVC_func(int *arr,int size){
              for(int i =0 ;i<size ;i++){
              	for(int j =i+1;j<size;j++){
                       if(arr[i]>arr[j] && i<j){
                           INVC++;
                       }
              	}
              }
              return INVC;
      }
};

int main() {
    int size = 10;
    int *arr = new int[size]{9, 6, 4, 5, 1, 3, 2, 0, 7, 8};  // Initialize a dynamic array with values

    Counting_inversion C;
    cout << C.INVC_func(arr, size) << endl;

    delete[] arr;  // Free dynamically allocated memory
    return 0;
}