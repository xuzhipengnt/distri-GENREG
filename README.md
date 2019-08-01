# Distri-GENREG

## Introduction

Distri-GENREG is the modified version for a regular graph generator (GENREG) that supports the parallel scale of thousands of CPU cores. For adapting to the cluster, we added a layer of  MPI wrap to schedule the tasks that can implement loading balance, which can make full use of all cores. 

If you are interested in the area of the regular graph or want to design some interconnection network for small-scale clusters or SOC,  you can try it. Also, if you are curious about the sequence of A068934(http://oeis.org/wiki/User:Jason_Kimberley/A068934) like me, you can try it on some clusters. We also provide a script for the SLURM management system and will add more options in the future. But if you want to join in the area of regular graph counting, I think you should have enough computing resources for supercomputers because Jason Kimberley has got many results 8 years ago, and the remaining parts are not easy to calculate and may cost expensive computing hour.

In July of 2019, we have used this program to promote n of A006820 from 22 to 23, which is the sequence of the number of connected regular simple graphs of degree 4 (or quartic graphs) with n nodes.  In this work, we cost almost 0.86 million core-hour (if you use one core, that may need about 99 years) and got the exact number of unlabeled regular graphs for order 32.  This work was supported by three large-scale clusters, they are SeaWulf located at Stony Brook University, Tianhe-1 located at Changshan, China, and Yachay IBM Power 8 cluster, Ecuador. Also. In this repository, we provide the original data of this work that can be verified.

During the initiation stage of this project, we didn't comment on our codes in detail, but we can supply help if you need it. In the future, we will format our code and support more architectures such as many-core.

About 2 years ago, I sent the email to Dr. Markus Meringer to enquire how to make the GENREG run on the large cluster and received his harmful reply. We also thank him for his encouragement here.

## Useage

If you are familiar with Linux, you run the makefile the compile the program and need to install MPICH or OpenMPI environments. In the program, we use one core to schedule tasks ad need two threads at least, so if you run the code in one thread, that would be meanless. 

If you are in the bash of the computing node, you can run this command directly

mpirun ./genreg 23 4 -a stdout -split 12 -m 1 5000 50000

Here, '-a stdout' is the essential parameter that outputs the message to the terminal but not files. '-m 1 5000 50000' means the task will be divided into 50000 blocks and then calculate from 1 to 50000.

If you are located in the login node of some cluster and the cluster use the SLURM schedule system,  you can modify 'run.slurm' then use the command 'sbatch' the submit your task.

## Copyright

The author of GENREG did not claim the copyright in 1995. And I think the modified version of GENREG should be GPL according to the sprint of open source.
