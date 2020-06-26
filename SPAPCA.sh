#!/bin/sh
#SBATCH --mem=10gb
#SBATCH --nodes=1
#SBATCH --qos=yourQOS
#SBATCH --time=12:00:00
#SBATCH --ntasks=1

fileresult=$1
number=$2

chmod 777 "$fileresult" 
/Yourpath/SPAPCA "$number" "$fileresult"
wait
