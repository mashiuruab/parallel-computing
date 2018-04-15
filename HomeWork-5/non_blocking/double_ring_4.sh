module load openmpi

algo=3
np=4

mpirun -n $np ./run $algo 32 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 64 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 128 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 256 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 512 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 1024 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 2048 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 4096 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 8192 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 16384 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 32768 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 65536 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 131072 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 262144 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 524288 >> result/double_ring/$np.result
mpirun -n $np ./run $algo 1048576 >> result/double_ring/$np.result