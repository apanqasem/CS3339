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
   * [Dynamic Thread Count and Performance Evaluation](#timing)
   * [Thread Count ans Scalability](#thread_count)
   
### <a name="install"></a> Installing OpenMP

OpenMP does not need to be installed separately. It is packaged with the compiler on your
system. Check the GCC version to make sure the compiler supports OpenMP


```bash
gcc --version
```

OpenMP has been supported since GCC 4.2, which implements OpenMP specification 2.5. To
ensure support for newer OpenMP specifications we need to have a recent version of GCC
installed. In particular, we want at least GCC 6 which provides support for OpenMP 4.5
which added significant enhancements over earlier versions. 

### <a name="compile"></a>Compiling and Running an OpenMP Program

To compile an OpenMP program, all that is needed is to pass the appropriate compiler flag. For GCC
(and Clang) this flag is `-fopenmp`. Consider the following Hello World program in C. 

```C
#include<stdio.h>
int main(int argc, char* argv[]) {
  printf("Hello World\n");
  return 0;
}
```

Let save this file to the current directory


```bash
cat > hello.c << EOF
#include<stdio.h>
int main(int argc, char* argv[]) {
  printf("Hello World\n");
  return 0;
}
EOF
```

We can compile this code with OpenMP with the following


```bash
gcc -o hello -fopenmp hello.c
```

We can run the resulting executable in the same manner as we would a regular sequential program


```bash
./hello
```

Of course, we have not added any parallelism in the code yet. So the result is uninteresting. But
even after adding parallelism, the process of compiling and running OpenMP programs will remain the
same. 


### <a name="directives"></a>OpenMP Compiler Directives

To parallelize with OpenMP we need to add directives or pragmas in the source code. OpenMP supports
a wide [range of
pragmas](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf). The most simplest
of these is the `parallel` pragma. Let us insert the pragma in our Hello World code. So that we have something to run in parallel we will also add another statement. 

```C
#include<stdio.h>
int main(int argc, char* argv[]) {
  #pragma omp parallel {
    printf("Hello World\n");
    printf("Goodbye World\n");
  }
  return 0;
}
```

Let's save this version. 


```bash
cat > hello.c << "EOF"
#include<stdio.h>
int main(int argc, char* argv[]) {
  #pragma omp parallel {
    printf("Hello World\n");
    printf("Goodbye World\n");
  }
  return 0;
}
EOF
```

All pragmas in OpenMP begin with `#pragma omp`. This is usually followed by a keyword which
describes the action to be performed. The action can be followed by a sequence of _clauses_ to
influence the prescribed action. For now, we will just look at the `parallel` pragma without any
clauses. A `pragma` is usually followed by a pair of curly braces to mark the block of code on which
the action is to be performed. Without the braces, the pragma will apply to the next statement only,
which is a behavior, we rarely want. 

We can now attempt to compile the OpenMP code using the `fopenmp` flag.


```bash
gcc -o hello -fopenmp hello.c 
```

#### What happened?

The compiler error message is a little cryptic. The problem here is that the 
opening `{` must be on a new line. If you prefer the style where the opening brace is placed on the
same line as the statement preceding a code block then it may take a little getting used to. The
above code can be fixed by simply moving the opening braces to the next line.


```bash
cat > hello.c << "EOF"
#include<stdio.h>
int main(int argc, char* argv[]) {
  #pragma omp parallel 
  {
    printf("Hello World\n");
    printf("Goodbye World\n");
  }
  return 0;
}
EOF
```

We can now build the code successfully.


```bash
gcc -o hello -fopenmp hello.c
```

#### What do we expect the output to be?

Let's run the program


```bash
./hello 
```

The behavior may not be exactly what you expected. Here's how the `parallel` directive works. 

  * the pragma marks a _parallel_ region in the program
  * at runtime OpenMP creates _n_ threads where _n_ is determined from the environment
  * each thread executes each statement in the block in parallel (i.e., an instance of block is
    executed _n_ times) 

#### Can we find out how many threads OpenMP created for the Hello World program?

### <a name="api"></a>OpenMP Runtime Library Routines 

We can use `wc` to count the number of lines in the output.


```bash
./hello | wc -l 
```

#### Why did OpenMP decide to create 4 threads? 

Generally, OpenMP will try to match the number threads to the available processing cores. Let's
check the number of available cores in our system


```bash
lscpu | head -6
```

We can modify this default behavior in several ways. One way to do this is via a call to [OpenMPs
runtime library](https://gcc.gnu.org/onlinedocs/libgomp/Runtime-Library-Routines.html). OpenMP
supports a large collection of runtime routines. To use these routines, we need include the OpenMP
header file.

```C
#include<omp.h>
```

We can then tell OpenMP to use a specific number of threads using the appropriately named function `omp_set_num_threads()`

```C
omp_set_num_threads(4);
```

Each thread created by OpenMP has an ID. This is different from the thread IDs used by the OS. We can obtain the thread ID using the `omp_get_thread_num()` function.

```C
int ID = omp_get_thread_num();
printf("Hello World from %d!\n", ID);
printf("Goodbye World from %d!\n", ID);
```

Let's save our changes. 


```bash
cat > hello.c << "EOF"
#include<stdio.h>
#include<omp.h>

int main(int argc, char* argv[]) {
  omp_set_num_threads(4);
  
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

Let's compile and run the program again.


```bash
gcc -o hello -fopenmp hello.c 
```


```bash
./hello 
```

Let's run the code again 


```bash
./hello
```

What can make two observations. 
  * outputs from different threads doesn't get printed out in the order of the thread IDs.   
  * different runs results in differents orders of the output. (you may need to run it a few 
    times)
 
This indicates that the threads are executing asyncrhonously. Success!

### <a name="timing"></a>Dynamic Thread Count and Performance Evaluation
Because we specified the thread count at compile-time, the above program will _always_  launched with 4 threads. threads. Generally, this is not a good approach when programming with OpenMP. We want better control over OpenMP threads and be able to specify the number of threads considering a variety of factors including the target CPU, input size and task granularity. To set the number of threads dynamically, we can pass the thread count to the program as a command-line argument.

```C
#include<stdio.h>
#include<stdlib.h> // for atoi 
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

Let's save this verison. 


```bash
cat > hello.c << EOF
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

We can measure the execution time of a parallel OpenMP program just like we would a sequential
program. Let's time the sequential version first. We can run the sequential version and time it as follows


```bash
gcc -o hello -fopenmp hello.c
```


```bash
time ./hello 1
```

`time` does not give us good enough resolution for this tiny program. We can use `perf` to get
*somewhat* better measurements.


```bash
perf stat ./hello 1
```

Now, let's run the code with 2 threads.


```bash
perf stat ./hello 2
```

_How much performance improvement do we get by running this code in parallel?_

This very simple code is not useful for doing any kind of performance evaluation. We will look at a slightly more complex code in the next tutorial.
