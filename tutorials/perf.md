## Performance evaluation and program execution demo

### Description 

A simple introduction to command-line program execution and performance evaluation. Covers the following

   * basic Linux commands 
   * command-line compilation with `gcc`
   * performance profiling with `perf`. 

### Outline 

* [Environment Set-up](#env)
* [Obtaining code samples](#git)
* [Building and executing](#gcc)
* [Measuring performance](#time)
* [Exploring a new architecture (POWER8)](#capi) 
* [Getting performance insight via `perf`](#perf)


### <a name="env"></a>Environment Set-up
   
##### (i) Login to remote linux system 

Log in to one of the CS servers using ssh

    ssh zeus.cs.txstate.edu

Available CS servers are zeus and eros. Both can be accessed from outside the university firewall. 

Set up a working directory for the experiments. 

List files in current directory 

```
ls
```

Almost all Linux commands will accept a set of options that can be used to control its
behavior. Options are passed at the command-line using a `-` followed by a single character. The
character corresponds to the particular option that you want enforced. Here are few useful flags for
the `ls` command.
 
List files in current directory including hidden files 
```
ls -a
```

List files and attributes in current directory reverse chronological order 

```
ls -ltr 
```

Create a directory
```
mkdir cs3339
```

Change to working directory
```
cd cs3339
```

Change to home directory
```
cd
```

Change to working directory
```
cd cs3339
```

##### (ii) Get familiar with the experimental environment

Get information about the OS and architecture. 

	uname 
	
Get more information (-a stands for all)
 
    uname -a

See who else is logged on and what they are doing 
 
    w
	
Look up specific user 

    finger 

List the processes that are currently running and report resource usage 
 
    top

Get CPU information 
    
	cat /proc/cpuinfo

Get memory information 

    cat /proc/meminfo


### <a name="git"></a>Obtaining code samples

Clone the course git repo on this server. 

	git clone https://git.txstate.edu/aq10/CS3339.git ~/CS3339.git

Copy the knapsack source and input files to your working directory 

    cp ~/CS3339.git/code_samples/knapsack/knapsack.cpp .
    cp ~/CS3339.git/code_samples/knapsack/input .
	
### <a name="gcc"></a>Building and executing 

Compile a C++ source. The `-c` option to `gcc` tells it to only compile the source. This option
doesn't perform any _linking_ and therefore doesn't result in a program that we can execute. 

    g++ -c knapsack.cpp
	ls -ltr 

If we want to build the executable then we need to omit the `-c` flag. 

    g++ -o knapsack knapsack.cpp
	ls -ltr 

There are many things happening behind scenes when going from a source to a binary executable. We
can inspect these steps by using the `-v` option. 

    g++ -v -o knapsack knapsack.cpp

The compiler's main job is to just generate the human-readable assembly. Subsequent steps are
conducted by tools (e.g., assembler, linker) that are packaged with the compiler. If we want to just
generate the assembly code then we can pass the `-S` option. 

    g++ -S knapsack.cpp
	ls -ltr 
	
Note, the relative size of the source, asssembly, object and executable files. 

To execute a program from the command-line, we simply need the name of the executable and its
location (_path_, in Linux terminology). 
	
    ./knapsack input
	
The knapsack program takes a command-line argument which is the name of an input file that holds the
data. 
    
### <a name="time"></a>Measuring performance 

**How do we measure the performance of a program?** 

We can use the `time` command to get a rough measure of the execution time. The terms _execution
time_ and _running time_ are synonymous. _Runtime_ means something different! 
	
    time ./knapsack input 

The `time` command reports three numbers. `real` time is the time that has elapsed during the
execution of the program. `user` time is the actual time the program is running on the
processor. `sys` is the time when the _system_ is doing some work either on behalf of this program
or some program. Often `real` time is roughly equal to `user` time + `sys` time 

Compilers implement many optimizations to try to improve the performance of a program. We can
specify the level of optimizations using the `-O` flags. By default, `gcc` will apply only a few
optimizations. This is referred to as level `-O0`. Let's rebuild the program at the highest optimization
level `-O3`.  

    g++ -o knapsack -O3 knapsack.cpp
    time ./knapsack input 
    
We can check the optimizations that are being applied at `-O3` with the `--help=optimizers` option. 

    gcc -Q -O3 --help=optimizers


### <a name="capi"></a>Exploring the system with a different architecture (POWER8) 

Log in to `capi.cs.txstate.edu` using ssh. capi is not visible outside the firewall. Accounts will
be created for all of you. 
    
    ssh capi.cs.txstate.edu

Check out the OS and architecture information on capi. 

    uname -a
    cat /proc/cpuinfo
    cat /proc/meminfo

Generate assembly code for knapsack 

    g++ -S knapsack.cpp

Notice how the instructions are different from those on zeus which is an x86 machine. 

Build the executable with full optimization and measure its performance. 

    gcc -o knapsack -O3 knapsack.cpp
    time ./knapsack input 


### <a name="perf"></a>Getting performance insight via `perf`

Most recent Linux distributions come with a performance evaluation tool called `perf`. This tool
probes the underlying hardware performance counters and can measure a variety of events
during program execution. More on this later in the semester. 

To use the `perf` tool, simply type `perf` followed by a `perf` command. The `list` command lists
the available performance events on this architecture. 

    perf list

The above only lists the _named_ events. Typically there are hundreds more on the system. 

To get a basic profile we can use the `stat` command, followed by the name the of the program we
want to profile. The program can be one that you wrote or any Linux command. 

    perf stat ls

Now let's profile the knapsack program. Note, for knapsack we need to indicate the path of the
executable and the input file name after the `stat` command. 

    perf stat ./knapsack input


