# cpp-omp-cray

## CPP runs:

1. Hop on a compute node with salloc and create a build directory

```
shubhp@nid006942:~/cpp-omp-cray> mkdir build && cd build
```
2. Run cmake
```
shubhp@nid006942:~/cpp-omp-cray/build> cmake ../
-- The C compiler identification is GNU 12.3.0
-- The CXX compiler identification is GNU 12.3.0
-- Cray Programming Environment 2.7.30 C
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /opt/cray/pe/craype/2.7.30/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Cray Programming Environment 2.7.30 CXX
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /opt/cray/pe/craype/2.7.30/bin/CC - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Looking for sgemm_
-- Looking for sgemm_ - found
-- Found BLAS: BLAS_LIBRARIES-PLACEHOLDER-FOR-EMPTY-LIBRARIES  
-- Configuring done
-- Generating done
-- Build files have been written to: /global/homes/s/shubhp/cpp-omp-cray/build
```
3. Run make
```
shubhp@nid006942:~/cpp-omp-cray/build> make
/usr/bin/cmake -S/global/homes/s/shubhp/cpp-omp-cray -B/global/homes/s/shubhp/cpp-omp-cray/build --check-build-system CMakeFiles/Makefile.cmake 0
/usr/bin/cmake -E cmake_progress_start /global/homes/s/shubhp/cpp-omp-cray/build/CMakeFiles /global/homes/s/shubhp/cpp-omp-cray/build//CMakeFiles/progress.marks
make  -f CMakeFiles/Makefile2 all
make[1]: Entering directory '/global/u2/s/shubhp/cpp-omp-cray/build'
make  -f CMakeFiles/benchmark-blas.dir/build.make CMakeFiles/benchmark-blas.dir/depend
make[2]: Entering directory '/global/u2/s/shubhp/cpp-omp-cray/build'
cd /global/homes/s/shubhp/cpp-omp-cray/build && /usr/bin/cmake -E cmake_depends "Unix Makefiles" /global/homes/s/shubhp/cpp-omp-cray /global/homes/s/shubhp/cpp-omp-cray /global/homes/s/shubhp/cpp-omp-cray/build /global/homes/s/shubhp/cpp-omp-cray/build /global/homes/s/shubhp/cpp-omp-cray/build/CMakeFiles/benchmark-blas.dir/DependInfo.cmake --color=
make[2]: Leaving directory '/global/u2/s/shubhp/cpp-omp-cray/build'
make  -f CMakeFiles/benchmark-blas.dir/build.make CMakeFiles/benchmark-blas.dir/build
make[2]: Entering directory '/global/u2/s/shubhp/cpp-omp-cray/build'
[ 50%] Building CXX object CMakeFiles/benchmark-blas.dir/benchmark.cpp.o
/opt/cray/pe/craype/2.7.30/bin/CC   -O3 -DNDEBUG -Wall -pedantic -march=native -MD -MT CMakeFiles/benchmark-blas.dir/benchmark.cpp.o -MF CMakeFiles/benchmark-blas.dir/benchmark.cpp.o.d -o CMakeFiles/benchmark-blas.dir/benchmark.cpp.o -c /global/homes/s/shubhp/cpp-omp-cray/benchmark.cpp
[100%] Linking CXX executable benchmark-blas
/usr/bin/cmake -E cmake_link_script CMakeFiles/benchmark-blas.dir/link.txt --verbose=1
/opt/cray/pe/craype/2.7.30/bin/CC -O3 -DNDEBUG -fopenmp CMakeFiles/benchmark-blas.dir/benchmark.cpp.o -o benchmark-blas 
make[2]: Leaving directory '/global/u2/s/shubhp/cpp-omp-cray/build'
[100%] Built target benchmark-blas
make[1]: Leaving directory '/global/u2/s/shubhp/cpp-omp-cray/build'
/usr/bin/cmake -E cmake_progress_start /global/homes/s/shubhp/cpp-omp-cray/build/CMakeFiles 0
```
4. Set OpenMP env variables
```
shubhp@nid006942:~/cpp-omp-cray/build> export OMP_NUM_THREADS=128 OMP_PROC_BIND=true OMP_PLACES=cores
```
5. Run benchmark
```
shubhp@nid006942:~/cpp-omp-cray/build> ./benchmark-blas -N 4096 -I 10
Description:

Working on problem size N=4096 

 Memory allocation time is : 0.033928 (sec) 
 Matrix fill time is : 0.272941 (sec) 
 Elapsed time is : 0.174299 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.053775 (sec) 
 Matrix fill time is : 0.287265 (sec) 
 Elapsed time is : 0.148723 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.055270 (sec) 
 Matrix fill time is : 0.285854 (sec) 
 Elapsed time is : 0.157127 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.055094 (sec) 
 Matrix fill time is : 0.284411 (sec) 
 Elapsed time is : 0.149465 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054696 (sec) 
 Matrix fill time is : 0.287056 (sec) 
 Elapsed time is : 0.158717 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054473 (sec) 
 Matrix fill time is : 0.284417 (sec) 
 Elapsed time is : 0.153285 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054689 (sec) 
 Matrix fill time is : 0.285571 (sec) 
 Elapsed time is : 0.150471 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054625 (sec) 
 Matrix fill time is : 0.285875 (sec) 
 Elapsed time is : 0.146026 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054533 (sec) 
 Matrix fill time is : 0.286132 (sec) 
 Elapsed time is : 0.148098 (sec) 

Working on problem size N=4096 

 Memory allocation time is : 0.054944 (sec) 
 Matrix fill time is : 0.285584 (sec) 
 Elapsed time is : 0.152830 (sec) 

 First of 10 iterations= 0.174299 (sec)
Flopcount: 137.472508 GFLOP
Best (7)      0.146026 sec     941.427918 GFLOPs
```

## For Python runs with cray-libsci

1. Hop on a compute node with salloc and load cray-python

```
shubhp@nid006942:~/cpp-omp-cray> ml cray-python
```

2. Set OpenMP env variables
```
shubhp@nid006942:~/cpp-omp-cray/build> export OMP_NUM_THREADS=128 OMP_PROC_BIND=true OMP_PLACES=cores
```

3. Run python-dgemm
```
shubhp@nid006942:~/cpp-omp-cray> python python-dgemm.py --nsize 4096
Requested Arguments:
  niterations : 10
  nsize       : 4096
  accelerator : False
  testseed    : None
Preparing Matrix arrays
Memory required: 384.000 MB
Time for Array Allocation (sec): 0.000026
Time for Array Initialization (sec): 8.663
Running matmul...
Synchronization Overhead (sec): 7.15e-07
First of 10 iterations (sec): 0.065254
FlopCount: 1.374725e+11
Iteration (int)   Time(s) Gflop/s
First (0)         0.06525  2106.7
Last (9)          0.02913  4719.4
Best (8)          0.02826  4864.9
```

Additional env settings for both runs:
```
shubhp@nid006942:~/cpp-omp-cray> env | grep OMP
PE_LIBSCI_OMP_REQUIRES= 
CRAY_LMOD_COMPILER=gnu/12.0
LMOD_FAMILY_COMPILER_VERSION=12.3
OMP_PROC_BIND=true
__LMOD_REF_COUNT_PE_MPICH_GENCOMPILERS_GNU=12.3:1
LMOD_FAMILY_GCC_COMPILER=gcc-native
PE_LIBSCI_GENCOMPILERS_GNU_x86_64=12.3
PE_LIBSCI_OMP_REQUIRES_openmp=_mp
LMOD_FAMILY_GCC_COMPILER_VERSION=12.3
PE_LIBSCI_VOLATILE_PKGCONFIG_PATH=/opt/cray/pe/libsci/23.12.5/@PRGENV@/@PE_LIBSCI_GENCOMPS@/@PE_LIBSCI_TARGET@/lib/pkgconfig
PAT_RT_PERFCTR_DISABLE_COMPONENTS=nvml,rocm_smi
OMP_PLACES=cores
LMOD_FAMILY_COMPILER=gcc-native
PE_MPICH_GENCOMPILERS_GNU=12.3
PE_LIBSCI_PKGCONFIG_VARIABLES=PE_LIBSCI_OMP_REQUIRES_@openmp@:PE_SCI_EXT_LIBPATH:PE_SCI_EXT_LIBNAME
OMP_NUM_THREADS=128
PE_LIBSCI_GENCOMPS_GNU_x86_64=123
```