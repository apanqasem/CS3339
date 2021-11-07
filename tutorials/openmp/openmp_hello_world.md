# Hello World in OpenMP

### Description

A very basic introduction to OpenMP. The demo walks through a Hello World program parallelized with
the `omp parallel` directive and discusses the importance and significance of thread count
using a matrix-scalar multiplication example. 

Covers the following directives and API

  * OpenMP directives: `parallel` and `parallel for`
  * OpenMP API: `omp_set_num_threads()`, `omp_get_thread_num()`
  
### Outline

   * [Installing OpenMP](#install)
   * [Compiling and Running an OpenMP Program](#compile)
   * [OpenMP Compiler Directives](#directives)
   * [OpenMP Runtime API](#api)
   * [Performance Evaluation](#timing)
   * [Thread Count ans Scalability](#thread_count)
   
### <a name="install"></a> Installing OpenMP

OpenMP does not need to be installed separately. It is packaged with the compiler on your
system. Check the GCC version to make sure the compiler supports OpenMP 

    (knuth)% gcc --version
    gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
    Copyright (C) 2017 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

OpenMP has been supported since GCC 4.2, which implements OpenMP specification 2.5. To
ensure support for newer OpenMP specifications we need to have a recent version of GCC
installed. In particular, we want at least GCC 6 which provides support for OpenMP 4.5
which added significant enhancements over earlier versions. 

### <a name="compile"></a>Compiling and Running an OpenMP Program

To compile an OpenMP program, all that is needed is to pass the appropriate compiler flag. For GCC
(and Clang) this flag is `-fopenmp`. Consider the following Hello World C program. 

```C
#include<stdio.h>

int main() {

  printf("Hello World\n");
  printf("Goodbye World!\n");
  return 0;
}
```
The above can be compiled with OpenMP with the following 

    (knuth)% gcc -o hello -fopenmp hello.c

We can run the resulting executable in the same manner as we would a regular sequential program

    (knuth)% ./hello

Of course, we have not added any parallelism in the code yet. So the result is uninteresting. But
even after adding parallelism, the process of compiling and running OpenMP programs will remain the
same. 


### <a name="directives"></a>OpenMP Compiler Directives

To parallelize with OpenMP we need to add directives or pragmas in the source code. OpenMP supports
a wide [range of
pragmas](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf). The most simplest
of these is the `parallel` pragma. Let us insert the pragma in our Hello World code. 

```C
#pragma omp parallel {		
  printf("Hello World!\n");
  printf("Goodbye World!\n");
}
```
All pragmas in OpenMP begin with `#pragma omp`. This is usually followed by a keyword which
describes the action to be performed. The action can be followed by a sequence of _clauses_ to
influence the prescribed action. For now, we will just look at the `parallel` pragma without any
clauses. A `pragma` is usually followed by a pair curly braces to mark the block of code on which
the action is to be performed. With the braces, the pragma will apply to the next statement only,
which is a behavior, we rarely want. 

We can now attempt to compile the OpenMP code using the `fopenmp` flag. 

    (knuth)% gcc -o hello -fopenmp hello0.c 
    hello0.c: In function ‘main’:
    hello0.c:7:24: error: expected ‘#pragma omp’ clause before ‘{’ token
    #pragma omp parallel {
                        ^
    hello0.c: At top level:
    hello0.c:11:3: error: expected identifier or ‘(’ before ‘return’
    return 0;
    ^~~~~~
    hello0.c:12:1: error: expected identifier or ‘(’ before ‘}’ token
    }
    ^


_What happened?_ 

The compiler error message is a little cryptic. The problem here is that the 
opening `{` must be on a new line. If you prefer the style where the opening brace is placed on the
same line as the statement preceding a code block then it may take a little getting used to. The
above code can be fixed by simply moving the opening braces to the next line. 

```C
#pragma omp parallel 
{		
  printf("Hello World!\n");
  printf("Goodbye World!\n");
}
```
We can now build the code successfully. 

    (knuth)% gcc -o hello -fopenmp hello.c

_What do we expect the output to be?_

Let's run the program 

    (knuth)% ./hello 
	
The behavior may not be exactly what you expected. Here's how the `parallel` directive works. 

  * the pragma marks a _parallel_ region in the program
  * at runtime OpenMP creates _n_ threads where _n_ is determined from the environment
  * each thread executes each statement in the block in parallel (i.e., an instance of block is
    executed _n_ times) 

_Can we find out how many threads OpenMP created for the Hello World program?_

### <a name="api"></a>OpenMP Runtime Library Routines 

We can use `wc` to count the number of lines in the output. 


    (knuth)% ./hello | wc -l 
	24


_Why did OpenMP decide to create 12 threads?_ 

Generally, OpenMP will try to match the number threads to the available processing cores. Let's
check the number of available cores in our system 

    (knuth)% lscpu | head -4
    Architecture:        x86_64
    CPU op-mode(s):      32-bit, 64-bit
    Byte Order:          Little Endian
    CPU(s):              12
    
We can modify this default behavior in several ways. One way to do this is via a call to [OpenMPs
runtime library](https://gcc.gnu.org/onlinedocs/libgomp/Runtime-Library-Routines.html). OpenMP
supports a large collection of runtime routines. To use these routines, we need include the OpenMP
header file. 

    #include<omp.h>

We can then tell OpenMP to use a specific number of threads using the appropriately named function
`omp_set_num_threads()` 

    omp_set_num_threads(4)

Each thread created by OpenMP has an ID. This is different from the thread IDs used by the OS. We
can obtain the thread ID using the `omp_get_thread_num()` function. 

    int ID = omp_get_thread_num();
    printf("Hello World from %d!\n", ID);
    printf("Goodbye World from %d!\n", ID);

Let's compile and run the program again. 

    (knuth)% gcc -o hello -fopenmp hello1.c 
    (knuth)% ./hello 
    Hello World from 2!
    Goodbye World from 2!
    Hello World from 0!
    Goodbye World from 0!
    Hello World from 1!
    Goodbye World from 1!
    Hello World from 3!
    Goodbye World from 3!

We can see that the output from the different threads is interleaved indicating the concurrency (and
non-determinism) of execution. 

### <a name="timing"></a>Performance Evaluation
We can measure the execution time of a parallel OpenMP program just like we would a sequential
program. Let's time the sequential version first. Instead of hard coding the number of threads, we can
pass the value to the program as a command-line argument. 

```C
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

int main(int argc, char* argv[]) {

  int num_threads;
  if (argc <= 1)
    num_threads = 1;
  else
    num_threads = atoi(argv[1]);

  omp_set_num_threads(num_threads);
```

Now we can run the sequential version and time it as follows 

    (knuth)% time ./hello 1
    Hello World from 0!
    Goodbye World from 0!

    real	0m0.004s
    user	0m0.001s
    sys	    0m0.004s

`time` does not give us good enough resolution for this tiny program. We can use `perf` to get
*somewhat* better measurements. 

	(knuth)% perf stat ./hello 1
    Hello World from 0!
    Goodbye World from 0!

    Performance counter stats for './hello 1':

          2.240399      task-clock (msec)         #    0.864 CPUs utilized          
                 0      context-switches          #    0.000 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               118      page-faults               #    0.053 M/sec                  
         3,788,857      cycles                    #    1.691 GHz                    
         2,289,566      stalled-cycles-frontend   #   60.43% frontend cycles idle   
         1,618,024      stalled-cycles-backend    #   42.70% backend cycles idle    
         3,607,090      instructions              #    0.95  insn per cycle         
                                                  #    0.63  stalled cycles per insn
           628,934      branches                  #  280.724 M/sec                  
            19,700      branch-misses             #    3.13% of all branches        

       0.002592641 seconds time elapsed

Now, let's run the code with 2 threads. 

    (knuth)% perf stat ./hello 2
    Hello World from 0!
    Goodbye World from 0!
    Hello World from 1!
    Goodbye World from 1!

    Performance counter stats for './hello 2':

          2.384980      task-clock (msec)         #    0.912 CPUs utilized          
                 1      context-switches          #    0.419 K/sec                  
                 0      cpu-migrations            #    0.000 K/sec                  
               121      page-faults               #    0.051 M/sec                  
         4,249,512      cycles                    #    1.782 GHz                    
         2,662,123      stalled-cycles-frontend   #   62.65% frontend cycles idle   
         1,932,917      stalled-cycles-backend    #   45.49% backend cycles idle    
         3,694,681      instructions              #    0.87  insn per cycle         
                                                  #    0.72  stalled cycles per insn
           654,539      branches                  #  274.442 M/sec                  
            21,580      branch-misses             #    3.30% of all branches        

       0.002616198 seconds time elapsed


### <a name="thread_count"></a>Thread Count and Scalability 

_How much performance improvement do we get by running this code in parallel?_

This very simple code is not useful for doing any kind of performance evaluation. Let's look at a code
that is slightly more complex. 

```C
for p(j = 0; j < M; j++)
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
printf("parallel loop = %3.2f ms\n", t0);
```
The above program scales the values in an array by a constant factor. The loop is parallelized with the
`parallel for` directive. This directive is an extension of the `parallel` directive and is applied
exclusively to the *next* for loop. The `parallel for` directive will equally divide the iterations
of the loop and run them in parallel. The number of threads to be created is passed via a command-line
argument. There's a built-in timer to record the execution time of the parallel loop. 

Let's build and execute the sequential version of the code. 


```
(knuth)% g++ -o scale scale.c -fopenmp
(knuth)% ./scale 1000 1
result = 578.00
parallel loop = 1936.35 ms
```

Let's run it with 2 threads. 

```
(knuth)% ./scale 1000 2
result = 578.00
parallel loop = 1251.09 ms
```

Note, even with this very simple code we are not able to double the performance with 2 threads.  Now
let's run it with 12 threads which is what OpenMP picked for this system. 

```
(knuth)% ./scale 1000 12
result = 578.00
parallel loop = 419.77 ms
(knuth)% 
```

_What if we kept on increasing the number of threads, do we expect more parallelism?_

```
(knuth)% ./scale 1000 32
result = 578.00
parallel loop = 373.80 ms
(knuth)% ./scale 1000 64
result = 578.00
parallel loop = 374.94 ms
(knuth)% ./scale 1000 128
result = 578.00
parallel loop = 375.71 ms
```

_Does this performance pattern reminds us of something?_

This program becomes compute-bound when the number of threads is substantially higher than the available
processing cores. The ideal number of threads for a given program depends on many factors. Often some
fine-tuning is necessary. For instance, let's run the `scale` with 16 threads. 

```
(knuth)% ./scale 1000 16
result = 578.00
parallel loop = 416.82 ms
```

This performance is worse than the performance achieved with 12 threads and 32 threads. 
