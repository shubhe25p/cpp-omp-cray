#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include <cmath> 

#include <cblas.h>
#include <string.h>
#include <unistd.h>
#include <omp.h>

void initialize_host_arrays(double* A, double* B, int n) {
    for(int j=0;j<n;j++){
      for(int k=0;k<n;k++){
         A[j*n+k] = j*sin(j) + k*cos(k);
         B[j*n+k] = k*cos(j) + j*sin(k);
      }
    }
}

void report_performance(double* time, int iterations, double size){

   std::cout << " First of " << iterations << " iterations= " << time[0] <<" (sec)" << std::endl;
   double flops = 2*(size/1000.0)*(size/1000.0)*(size/1000.0) + 2*(size/10000.0)*(size/100000.0);
   std::cout << "Flopcount: " << flops <<" GFLOP" << std::endl;
   std::vector<double> gflops;
   double max=0.0;
   int index=0;
   for(int i=0;i<iterations;i++){
      gflops.push_back(flops/time[i]);
      if(gflops[i] > max){
         max = gflops[i];
         index=i;
      }
   }
   std::cout << "Best (" << index << ")      " << time[index] << " sec     " << gflops[index] << " GFLOPs" << std::endl;

}

/* The benchmarking program */
int main(int argc, char** argv) 
{
   std::cout << "Description:\t" << std::endl << std::endl;

   // check to see if there is anything on the command line:
   // -N nnnn    to define the problem size
   int cmdline_N = -1;
   int cmdline_I = -1; 
   int c;

   while ( (c = getopt(argc, argv, "N:I:")) != -1) {
      switch(c) {
         case 'N':
            cmdline_N = std::atoi(optarg == NULL ? "-999" : optarg);
            // std::cout << "Command line problem size: " << cmdline_N << std::endl;
            break;
         case 'I':
            cmdline_I = std::atoi(optarg == NULL ? "10" : optarg);
            break;
      }
   }


   std::cout << std::fixed << std::setprecision(6);

   std::vector<int> test_sizes;
   std::vector<double> exec_time;

   if (cmdline_N > 0)
      test_sizes.push_back(cmdline_N);

   /* For each test size */
   for (int i=0;i<cmdline_I;i++)
   {
   for (int n : test_sizes) 
   {
         std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
         std::chrono::duration<double> elapsed;
      printf("Working on problem size N=%d \n\n", n);

         // allocate memory for 6 NxN matrics
         start_time = std::chrono::high_resolution_clock::now();

         std::vector<double> buf(3 * n * n);
         double* A = buf.data() + 0;
         double* B = A + n * n;
         double* C = B + n * n;
                           
         end_time = std::chrono::high_resolution_clock::now();

         elapsed = end_time - start_time;
         
         std::cout << " Memory allocation time is : " << elapsed.count() << " (sec) " << std::endl;

         // initialize array
         start_time = std::chrono::high_resolution_clock::now();
         initialize_host_arrays(A, B, n);
         end_time = std::chrono::high_resolution_clock::now();

         elapsed = end_time - start_time;
         std::cout << " Matrix fill time is : " << elapsed.count() << " (sec) " << std::endl;

         /* DGEMM call: 
               C = beta*C + alpha*A*B;
               For beta=0, alpha=1

               C=AB
           */
         start_time = std::chrono::high_resolution_clock::now();
         cblas_dgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, n, n, n, 1., B, n, A, n, 0. , C, n);
         end_time = std::chrono::high_resolution_clock::now();

         elapsed = end_time - start_time;

         std::cout << " Elapsed time is : " << elapsed.count() << " (sec) \n" << std::endl;
         exec_time.push_back(elapsed.count());

   } // end loop over problem sizes
   }
   report_performance(exec_time.data(), cmdline_I, (double)cmdline_N);
   return 0;
}

// EOF
