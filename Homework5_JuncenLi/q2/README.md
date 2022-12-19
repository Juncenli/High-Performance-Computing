### Using P100
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=04:00:00 /bin/bash`

### Load modules
- `module load gcc/6.4.0`
- `module load cuda/10.2`

### Compile Question a)
- `nvcc q2a.cu -o q2a`


### Run Question a)
- `./q2a`

