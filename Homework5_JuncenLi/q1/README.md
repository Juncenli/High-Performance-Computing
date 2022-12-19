### Using P100
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=04:00:00 /bin/bash`

### Load modules
- `module load gcc/6.4.0`
- `module load cuda/10.2`

### Compile Question a)
- `nvcc q1a.cu -o q1a`

### Compile Question b)
- `gcc q1b.c -o q1b -fopenmp`

### Run Question a)
- `./q1a`


### Run Question b)
- `./q1b`
