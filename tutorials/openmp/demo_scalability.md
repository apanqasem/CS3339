## [Demo] OpenMP Performance Scalability 
[D2] Heterogeneous Programming with OpenMP  
Apan Qasem [\<apan@txstate.edu\>](apan@txstate.edu)

### Description

This interactive demo discusses the importance and significance of thread count in OpenMP
applications. It is assumed that students know how to write a Hello World program in OpenMP (e.g.,
have completed the ([Hello World in OpenMP](demo_hello_world.md)) tutorial. 

The demo also introduces the `parallel for` directive. A simple matrix-scalar multiplication code is
used as a running example. 

### Outline 

   * [The OpenMP Hello World Program](#hello)
   * [Parallelizing with `parallel for`](#pragma) 
   * [Thread Count ans Scalability](#thread_count)


### <a name="hello"></a>The OpenMP Hello World Program

Below is the Hello World program with OpenMP parallelization that we wrote in our previous tutorial
([Hello World in OpenMP](demo_hello_world.md)).

```C
#include<stdio.h>
#include<stdlib.h>  // for atoi 
#include<omp.h>

int main(int argc, char* argv[]) {

  int num_threads;
  if (argc <= 1)
    num_threads = 1;
  else
    num_threads = atoi(argv[1]);

  omp_set_num_threads(num_threads);
  #pragma omp parallel 
  {
    int ID = omp_get_thread_num();
    printf("Hello World from %d!\n", ID);
    printf("Goodbye World from %d!\n", ID);
  }
  return 0;
}  
```

Let's save this file


```bash
cat > hello.c << "EOF"
#include<stdio.h>
#include<stdlib.h>  // for atoi 
#include<omp.h>

int main(int argc, char* argv[]) {

  int num_threads;
  if (argc <= 1)
    num_threads = 1;
  else
    num_threads = atoi(argv[1]);

  omp_set_num_threads(num_threads);
  #pragma omp parallel 
  {
    int ID = omp_get_thread_num();
    printf("Hello World from %d!\n", ID);
    printf("Goodbye World from %d!\n", ID);
  }
  return 0;
} 
EOF
```

Let us re-run the sequential version and time the run.


```bash
gcc -o hello -fopenmp hello.c
time ./hello 1
```

The Linux `time` command doesn't really give us satisfactory resolution for measuring the
performance of this _tiny_ program. We can use
[`perf`](https://perf.wiki.kernel.org/index.php/Main_Page) to get better measurements.


```bash
perf stat ./hello 1
```

Now, let's run the code with 2 threads.


```bash
perf stat ./hello 2
```

_How much performance improvement do we get by running this code in parallel?_

None! This very simple code is not useful for doing any kind of performance analysis. 

### <a name="pragma"></a>Parallelizing with `parallel for`

Let's look at a code that is slightly more complex.

```C
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#include <omp.h>

#define REPS 100

double t0;
double mysecond() {
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int main(int argc, char *argv[]) {
  float **a, **b;
  
  int M = atoi(argv[1]);
  int N = atoi(argv[2]);

  omp_set_num_threads(N);

  a = (float **) malloc(sizeof(float *) * M);
  b = (float **) malloc(sizeof(float *) * M);
  
  int i, j, k;
  for (i = 0; i < M; i++) {
    a[i] = (float *) malloc(sizeof(float) * M);
    b[i] = (float *) malloc(sizeof(float) * M);
  }

  for (j = 0; j < M; j++)
    for (i = 0; i < M; i++)
      b[i][j] = i + j;

  t0 = mysecond();
#pragma omp parallel for 
  for (int k = 0; k < REPS; k++) {
    for (int j = 0; j < M; j++) 
      for (int i = 0; i < M; i++)
	   a[i][j] = b[i][j] * 17;
  }

  t0 = (mysecond() - t0) * 1.e3;

  /* print an arbirtrary value from the result array */
  printf("result = %3.2f\n", a[17][17]);
  printf("parallel loop = %3.2f ms\n", t0);

  return 0;

}
```

Lets save this file. 


```bash
cat > scale.c << "EOF"
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#include <omp.h>

#define REPS 100

double t0;
double mysecond() {
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

int main(int argc, char *argv[]) {
  float **a, **b;
  
  int M = atoi(argv[1]);
  int N = atoi(argv[2]);

  omp_set_num_threads(N);

  a = (float **) malloc(sizeof(float *) * M);
  b = (float **) malloc(sizeof(float *) * M);
  
  int i, j, k;
  for (i = 0; i < M; i++) {
    a[i] = (float *) malloc(sizeof(float) * M);
    b[i] = (float *) malloc(sizeof(float) * M);
  }

  for (j = 0; j < M; j++)
    for (i = 0; i < M; i++)
      b[i][j] = i + j;

  t0 = mysecond();
#pragma omp parallel for 
  for (int k = 0; k < REPS; k++) {
    for (int j = 0; j < M; j++) 
      for (int i = 0; i < M; i++)
        a[i][j] = b[i][j] * 17;
  }

  t0 = (mysecond() - t0) * 1.e3;

  /* print an arbirtrary value from the result array */
  printf("result = %3.2f\n", a[17][17]);
  printf("parallel loop = %3.2f ms\n", t0);

  return 0;

}
EOF
```

The above program scales the values in an array by a constant factor. The loop is parallelized with the
`parallel for` directive. This directive is an extension of the `parallel` directive and is applied
exclusively to the *next* for loop. The `parallel for` directive will equally divide the iterations
of the loop and run them in parallel. The number of threads to be created is passed via a command-line
argument. There's a built-in timer to record the execution time of the parallel loop. 



### <a name="thread_count"></a>Thread Count and Scalability 

Let's build and execute the sequential version of the code.


```bash
g++ -o scale scale.c -fopenmp
./scale 1000 1
```

Let's run it with 2 threads.


```bash
./scale 1000 2
```

The parallel version runs significantly faster. However note, even with this very simple code we are
not able to double the performance when we increase the number of threads from 1 to 2. 

#### Why?

See [Heterogeneous Computing: Elementary Notions](https://github.com/TeachingUndergradsCHC/modules/tree/master/Fundamentals/elementary_notions) for one explanation. 

Let's check the number of available cores on this system



```bash
lscpu | head -6
```

Now, we will try to maximize the parallelization by running the code with a thread count that matches the number of cores. OpenMP would generally pick this thread count for this system if we did not specify the it ourselves.


```bash
./scale 1000 4
```

_Does it give us more performance?_

On most systems we will see an increase in performance. But not proportional to the number of threads used. 

_What if we kept on increasing the number of threads, do we expect to get more parallelism?_


```bash
./scale 1000 32
./scale 1000 64
./scale 1000 128
```

#### Does this performance pattern reminds us of something? 

This program becomes [compute-bound](https://en.wikipedia.org/wiki/CPU-bound) when the number of
threads is substantially higher than the available processing cores. At that point increasing the
number of threads doesn't give us any benefits (in fact in some cases it can actually hurt due to
thread creation overhead). 

The ideal number of threads for a given program depends on many factors. Often some fine-tuning is
necessary. 

### Exercise 

Compile and run the `matrix-scale` code on your own machine with increasing number of
threads. What is the ideal thread count?
