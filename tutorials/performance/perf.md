## Performance Profiling with `perf`
CS3339, Fall 2021

Apan Qasem [\<apan@txstate.edu\>](apan@txstate.edu)


### Description 

A  _very_ simple introduction to performance profiling with `perf`. Also, covers the following

   * hardware performance counters and performance events  
   * relative performance and normalized performance   
   * Tools: `hwloc`  
   * Linux utilities: `awk`, `sed`  

### Outline 

  * [Environment Set-up](#env)
  * [Performance Measurement](#perf_measure)
  * [`perf` Basics](#perf)
  * [Normalized Performance](#norm_perf)

### <a name="env"></a>Environment Set-up
   

##### (i) Login to remote linux system 

     ssh knuth.cs.txstate.edu 

Set up a working directory for the experiments. 

     mkdir perf_experiments 
	 cd perf_experiments 

##### (ii) Get familiar with the experimental environment

Get information about the OS and architecture. 
	
    uname -a
    
See who else is logged on and what they are doing 
 
    w
	
List the processes that are currently running and report resource usage 
 
    top

Get CPU information 
    
	cat /proc/cpuinfo

Get memory information 

    cat /proc/meminfo

The `hwloc` software package provides command-line tools and a C API to probe the system and get
a more detailed information of compute and memory resources. `hwloc` is usually not pre-installed. It
distributed with BSD licence and can be obtained from the [OpenMPI project
website](https://www.open-mpi.org/projects/hwloc/). `hwloc` has several command-line tools, the most
basic will give a hierarchical map of the compute elements and memory units. 

    hwloc-ls
	
##### (iii) Obtain code samples

Clone the course git repo on this server. 

	git clone https://git.txstate.edu/aq10/CS3339.git ~/CS3339.git

Copy the matrix-vector multiplication source file (`matvec.c`) to your working directory 

    cp ~/CS3339.git/code_samples/matvec.c .
	
##### (iv) Build and execute

Build the code. 

	g++ -o matvec matvec.c

Run the executable 

    ./matvec 2000 200

### <a name="perf_measure"></a>Performance Measurement

**How do we measure the performance of a program?** 

We can use the `time` command to get a rough measure of the execution time. The terms _execution
time_ and _running time_ are synonymous. Runtime means something different! 

    time ./matvec 2000 200

The `time` command reports three numbers. `real` time is the time that has elapsed during the
execution of the program. `user` time is the actual time the program is running on the
processor. `sys` is the time when the _system_ is doing some work either on behalf of this program
or some program. Often `real` time is roughly equal to `user` time + `sys` time 

**Are we happy with this performance of matvec?**

#### Relative performance 

Login to another remote Linux system and create a working directory. 
	
	ssh capi.cs.txstate.edu 
    mkdir perf_experiments 
	cd perf_experiments 
	
Check out the environment. 

    uname -a 
	cat /proc/cpuinfo 
	hwloc-ls 
	g++ --version 
	

Clone the course git repo on this server and copy the matrix-vector multiplication code to the working directory.
	
	git clone https://git.txstate.edu/aq10/CS3339.git ~/CS3339.git
    cp ~/CS3339.git/code_samples/matvec.c .

Build and run the `matvec` code with the same arguments and record the execution time. 

    g++ -o matvec matvec.c
    time ./matvec 2000 200


**Which system is doing better? Do the results match your expectation?** 

Minimum execution time does not necessarily imply the best performance! There are many factors to
consider. 

### <a name="perf"></a>`perf` Basics

Let's go back to our first machine. 

We can check if `perf` is installed just by typing the `perf` command. 

     perf

Recent versions of Ubuntu is likely to have `perf` pre-installed. If `perf` is not installed we can
install it with the following.

     sudo apt-get install linux-tools-common linux-tools-generic linux-tools-`uname -r`

Notice the use of back ticks in the above command. You need the `linux-tools-*` package that matches
your kernel. 

Get a basic profile of the `ls` command.

    perf stat ls

Get a basic profile of the matrix-vector multiplication code 

    perf stat ./matvec 2000 200

**Do we have any new insight about the performance of matvec?**

The set of performance metrics reported with `perf stat` are not the only ones we can get from
`perf`. The `perf` tool allows us to measure a measure a large number of program _events_. To find
the list of available performance events we can use the `perf list` command. 

    perf list

The above only lists the _named_ events. Typically there are hundreds more on the system. We will see how
to access those other events later in the tutorial. 

To get the number of loads and stores that go to the last-level cache (LLC) we can use the following
command with the `--event` option 

    perf stat --event LLC-loads,LLC-stores ./matvec 2000 200


**Do we have any new insight about the performance of matvec?**

### <a name="norm_perf"></a>Normalized performance

Execution time is not always a good measure of performance. Programs that execute more instructions
or those that process more data will have a longer execution time. That does not necessarily mean
that its performance is any worse that another program that executes fewer instructions. 

To get a better understanding of performance, we need a way to _normalize_ performance across
programs. One way to do this is to use a _throughput_ metrics. Throughput metrics measure
performance as a rate of _something_. For example, operating system performance may be measured in
number of tasks completed. FLOPs/sec counts the number of completed floating-operations per
second. This is the _de facto_ performance metric for HPC applications. This metric is also used to
rank the fastest supercomputers in the world by [top500.org](https://www.top500.org/). 

**How do we measure the FLOPS for `matvec`?**

We need to first find the event that corresponds to the execution of a floating-point
operation. This is not a named event. So we will need to dig up the hex-code. The code for the FP
event is `r538010`. We can now count the number of FP operations with perf

    perf stat -e r538010 ./matvec 2000 200


`perf` will not give you the FLOPS directly but we can write a short script to calculate it. 

	  # dump perf out to tmp file 
      perf stat -e r538010 ./matvec 2000 200 2> tmp.prof
       
	  # extract flop count
      flops=`cat tmp.prof | grep r538010  | awk '{print $1}' | sed 's/,//g'`
     
	  # extract number of seconds 
      secs=`cat tmp.prof | grep "elapsed"  | awk '{print $1}'`
  
	  # calculate FLOPS
      FLOPS=`echo $flops $secs | awk '{printf "%3.2f", ($1/1e+09)/$2}'`
 
      # print the result
	  echo "Performance = $FLOPS GFLOPS/s"






