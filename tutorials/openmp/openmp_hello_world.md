## Hello World in OpenMP 
Apan Qasem [\<apan@txstate.edu\>](apan@txstate.edu)

### Description

An in-class interactive walk-through of the Hello World program, parallelized using OpenMP. 


### Outline 

  * [Setting up OpenMP in Linux](#env)
  * [Compiling and running an OpenMP program](#compile) (`gcc` command-line)
  * [OpenMP pragmas:](#pragma)  `parallel`
  * [OpenMP API:](#api) `omp_set_num_threads(), omp_get_num_threads(), omp_get_thread_num()`


### <a name="env"></a>Setting up OpenMP in Linux
All mainstream compilers today provide integrated support for OpenMP. Each compiler has its own
implementation of the OpenMP standard. The OpenMP libraries and header files are packaged and
distributed with the compiler. So, no software packages need to be installed to build and run OpenMP
applications as long as there is a more-or-less recent compiler installed on the system. 

We can check the version of the compiler in our system as follows (ada is the name of the
machine where the commands in this demo were run). GCC ...


```bash
!gcc --version
```

... and LLVM


```bash
!clang --version
```

OpenMP has been supported since GCC 4.2, which implements OpenMP specification 2.5. To ensure support for newer OpenMP specifications we need to have a recent version of GCC installed. In particular, we want at least GCC 6 which provides support for OpenMP 4.5 which added significant enhancements over earlier versions.

### <a name="compile"></a>Compiling and running an OpenMP program

Below is the canonical Hello World program written in C.


```bash
%%writefile hello.c
#include<stdio.h>
int main() {
  printf("Hello World!\n");
  return 0;
}

```

We will implement an OpenMP version of this program. Generally, the first step in writing an OpenMP
program is including the header file (although in this trivial example we could have done without this)


```bash
%%writefile hello.c
#include<omp.h>
#include<stdio.h>
int main() {
  printf("Hello World!\n");
  return 0;
}
```

On Linux systems, `omp.h` is located `/usr/include`. Since this is in the compiler's search path for
header files there is no need to specify an include path (with the `-I` flag) in the compilation
command. We can compile and create an executable with the following command.


```bash
!gcc -o hello -fopenmp hello.c
```

The only difference from a regular build command is the inclusion of the `-fopenmp` flag. This flag
tells `gcc` that we are building an OpenMP application. We can now execute this  program from the
command-line just like a serial program.


```bash
!./hello
```

Of course, we have not added any parallelism in the code yet. So the result is uninteresting. But
even after adding parallelism, the process of compiling and running OpenMP programs will remain the
same. 

### <a name="pragma"></a>OpenMP pragmas

To parallelize with OpenMP we need to add directives or [pragmas](https://gcc.gnu.org/onlinedocs/cpp/Pragmas.html) in the source code. OpenMP supports
a wide [range of
pragmas](https://www.openmp.org/wp-content/uploads/OpenMP-4.5-1115-CPP-web.pdf). All pragmas have the following basic format

```C
#pragma omp <directive> [ options ]
```

`#pragma` tells the compiler that this line is to be processed by a pre-processor (not the compiler
    itself). `omp` says that the directive is to be processed by OpenMP. `<directive>` specifies the
    action to be taken on the code that immediately follows the pragma. The `<directive>` can be
    followed by a set of optional arguments. In OpenMP terminology, these arguments are called
    *clauses* (more on this in the next demo).  


**The `parallel` pragma:** One of the simplest pragmas in OpenMP is the `parallel` directive. It can
   be used to parallelize a block of code within an application. We will insert the parallel
   directive into our Hello World program.


```bash
%%writefile hello.c

# include<stdio.h>
# include<omp.h>
int main() {
  #pragma omp parallel
  printf("Hello World!\n");
  return 0;
}
```

This directive will execute the `printf` statement in parallel. This means that OpenMP will create
    _n_ threads where each thread will execute an instance of the `printf` statement. All _n_
    threads will execute this statement in parallel. We can build and execute this code as before.

_Can we predict the output?_


```bash
!gcc -o hello -fopenmp hello.c
!./hello 
```

_How many threads were created?_
	
**Thread count:** We can use the `wc` utility to count the number of lines of output from any program.


```bash
!./hello | wc -l 
```

**pragma scoping rules:** By default OpenMP pragmas apply to the next statement only. This is often
    not very useful for parallelization as we just saw with our first Hello World example. If we
    want the `pragma` to have an impact on a block of code then we can enclose the region with curly
    braces `{}` (_almost_ similar to what we do in C/C++)


```bash
%%writefile hello.c

# include<stdio.h>
# include<omp.h>
int main() {
  #pragma omp parallel {
     printf("Hello World!\n");
  }
  return 0;
}
```

_Why is the compiler complaining?_ 

**Compiler quirks:** The compiler error message is a little cryptic. The problem here is that unlike C/C++, blocks in OpenMP _must_ start on a newline. Remember, OpenMP directives are being processed by the pre-processor, not the compiler. Not being able to place the opening brace on the same line is a small sacrifice in style for some of us. The above code can be fixed by simply moving the opening braces to the next line.


    



```bash
%%writefile hello.c

#include<stdio.h>
#include<omp.h>
int main() {
  #pragma omp parallel 
  {
     printf("Hello World!\n");
  }
  return 0;
}
```

Let's compile this version.


```bash
!gcc -o hello -fopenmp hello.c 
!./hello 
```

Parallelizing a single statement doesn't really allow us to observe the parallel effects. Let's make the code a little more interesting. We will add a second statement to the parallel block. 


```bash
%%writefile hello.c
#include<stdio.h>
#include<omp.h>
	
int main() {
	
  omp_set_num_threads(4);
  #pragma omp parallel
  {
    printf("Hello World\n");  
    printf("Goodbye World\n");
  }
  return 0;
}
```

Let's compile this version and run it. 


```bash
!gcc -o hello -fopenmp hello.c 
```

_What do we expect the output to be?_

Let's run the program 


```bash
!./hello
```

Let's run it again and count the number of lines in the output


```bash
!./hello | wc -l
```

_How many threads were created? Can we guess why?_

Generally, OpenMP will try to match the number threads to the available processing cores. Let's check the number of available cores in our system


```bash
!lscpu | head -4
```

**`parallel` semantics:**  We can tell by the interleaving of Hello and Goodbye statements that the program is running in parallel. But the output may not be exactly what you expected. The two statements within the block are not in running parallel by themselves. Instead this is what is happening 

* OpenMP has created a bunch of threads (we will see how OpenMP makes this decision a little bit later) 
* each thread is executing both statements in the block
* all threads are running in parallel 

We can tell by the interleaving of Hello and Goodbye statements that the program is running in parallel. 
Of course, in real programs, we will want more control over the parallel execution. For that we need help from the OpenMP API. 



### <a name="api"></a>OpenMP API
OpenMP provides an extensive API to get information from executing threads and to configure the
   parallel execution environment. We will look at three of these here. 
    

* `omp_set_num_threads()` allows us to tell OpenMP how many threads it should in a parallel block of code
* `omp_get_num_threads()` gives us the number of threads that OpenMP is actually using. This function must be called from inside a parallel block. If called from outside it returns 1. 
* Each thread created by OpenMP has a unique ID (this is different from the thread ID maintained by the OS). The thread ID can be retrieved at runtime with `omp_get_thread_num()`. 
   
Let us now use these functions to track and control the parallel execution of our Hello World program. To use these functions we need include the OpenMP header file, which we have already done. 


```bash
%%writefile hello.c

#include<stdio.h>
#include<omp.h>
	
int main() {
	
  omp_set_num_threads(4);
  #pragma omp parallel
  {
    printf("Hello World from thread %u of %u.\n", omp_get_thread_num(), omp_get_num_threads());
    printf("Goodbye World from thread %u of %u.\n", omp_get_thread_num(), omp_get_num_threads());
  }
  return 0;
}
```

This program limits the number of OpenMP threads to 4. The parallel segment then prints out the ID
		of each thread created by OpenMP and the total number of threads.


```bash
!gcc -o hello -fopenmp hello.c
!./hello 
```

The number of threads in `omp_set_num_threads()` does not have to be a compile-time constant. It can be determined at runtime.
