module load openmpi

algo=1
np=16

mpirun -n $np ./run $algo 32 >> result/linear/$np.result
mpirun -n $np ./run $algo 64 >> result/linear/$np.result
mpirun -n $np ./run $algo 128 >> result/linear/$np.result
mpirun -n $np ./run $algo 256 >> result/linear/$np.result
mpirun -n $np ./run $algo 512 >> result/linear/$np.result
mpirun -n $np ./run $algo 1024 >> result/linear/$np.result
mpirun -n $np ./run $algo 2048 >> result/linear/$np.result
mpirun -n $np ./run $algo 4096 >> result/linear/$np.result
mpirun -n $np ./run $algo 8192 >> result/linear/$np.result
mpirun -n $np ./run $algo 16384 >> result/linear/$np.result
mpirun -n $np ./run $algo 32768 >> result/linear/$np.result
mpirun -n $np ./run $algo 65536 >> result/linear/$np.result
mpirun -n $np ./run $algo 131072 >> result/linear/$np.result
mpirun -n $np ./run $algo 262144 >> result/linear/$np.result
mpirun -n $np ./run $algo 524288 >> result/linear/$np.result
mpirun -n $np ./run $algo 1048576 >> result/linear/$np.result