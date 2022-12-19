## Using p100 gpu

- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=01:00:00 /bin/bash`

## Compile

- `module load gcc/6.4.0`

- `module load cuda/10.2`

- `nvcc matmulCUDA.cu -o matmulCUDA_p100`

- `./matmulCUDA_p100`




## Using k80 gpu

- `srun --partition=gpu --nodes=1 --pty --gres=gpu:k80:1 --ntasks=1 --mem=4GB --time=01:00:00 /bin/bash`

## Compile

- `module load gcc/6.4.0`

- `module load cuda/10.2`

- `nvcc matmulCUDA.cu -o matmulCUDA_k80`

- `./matmulCUDA_k80`

