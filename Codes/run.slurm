#!/bin/bash
#
#SBATCH --job-name=GENREG-23K4
#SBATCH --ntasks-per-node=40
#SBATCH --nodes=2
#SBATCH --time=168:00:00
#SBATCH -p extended-40core
export start=$1
export end=$2
module load shared
module load anaconda/3
echo ----Task----
echo $start
echo $end
echo ------------
mpirun -n 80 ./genreg 23 4 -a stdout -split 12 -m $start $end 50000
#/usr/sbin/sshd -f /gpfs/home/zhipxu/sshd_config -E /gpfs/home/zhipxu/sshd.log
#./lammps > err.txt
