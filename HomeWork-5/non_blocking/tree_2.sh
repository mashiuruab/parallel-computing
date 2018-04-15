module load openmpi

algo=4
np=2

mpirun -n $np ./run $algo 32 >> result/tree/$np.result
mpirun -n $np ./run $algo 64 >> result/tree/$np.result
mpirun -n $np ./run $algo 128 >> result/tree/$np.result
mpirun -n $np ./run $algo 256 >> result/tree/$np.result
mpirun -n $np ./run $algo 512 >> result/tree/$np.result
mpirun -n $np ./run $algo 1024 >> result/tree/$np.result
mpirun -n $np ./run $algo 2048 >> result/tree/$np.result
mpirun -n $np ./run $algo 4096 >> result/tree/$np.result
mpirun -n $np ./run $algo 8192 >> result/tree/$np.result
mpirun -n $np ./run $algo 16384 >> result/tree/$np.result
mpirun -n $np ./run $algo 32768 >> result/tree/$np.result
mpirun -n $np ./run $algo 65536 >> result/tree/$np.result
mpirun -n $np ./run $algo 131072 >> result/tree/$np.result
mpirun -n $np ./run $algo 262144 >> result/tree/$np.result
mpirun -n $np ./run $algo 524288 >> result/tree/$np.result
mpirun -n $np ./run $algo 1048576 >> result/tree/$np.result