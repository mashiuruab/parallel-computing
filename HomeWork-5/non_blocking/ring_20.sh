module load openmpi

algo=2
np=20

mpirun -n $np ./run $algo 32 >> result/ring/$np.result
mpirun -n $np ./run $algo 64 >> result/ring/$np.result
mpirun -n $np ./run $algo 128 >> result/ring/$np.result
mpirun -n $np ./run $algo 256 >> result/ring/$np.result
mpirun -n $np ./run $algo 512 >> result/ring/$np.result
mpirun -n $np ./run $algo 1024 >> result/ring/$np.result
mpirun -n $np ./run $algo 2048 >> result/ring/$np.result
mpirun -n $np ./run $algo 4096 >> result/ring/$np.result
mpirun -n $np ./run $algo 8192 >> result/ring/$np.result
mpirun -n $np ./run $algo 16384 >> result/ring/$np.result
mpirun -n $np ./run $algo 32768 >> result/ring/$np.result
mpirun -n $np ./run $algo 65536 >> result/ring/$np.result
mpirun -n $np ./run $algo 131072 >> result/ring/$np.result
mpirun -n $np ./run $algo 262144 >> result/ring/$np.result
mpirun -n $np ./run $algo 524288 >> result/ring/$np.result
mpirun -n $np ./run $algo 1048576 >> result/ring/$np.result