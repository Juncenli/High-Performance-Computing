### Using P100
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=01:00:00 /bin/bash`

### Using A100
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:a100:1 --ntasks=1 --mem=4GB --time=01:00:00 /bin/bash`


### Load modules
- `module add hpc_sdk`
  
- `module load cuda/11.7`

### Compile
- `nvcc VecAddCUDA.cu -o VecAddCUDA`

- `pgcc -acc -Minfo=accel VecAddOpenACC.c -o VecAddOpenACC`
  
### Run 
- `./VecAddCUDA`

- `./VecAddOpenACC`