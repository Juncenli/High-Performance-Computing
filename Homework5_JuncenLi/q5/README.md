### Using P100
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=04:00:00 /bin/bash`

### Load modules
- `module load gcc/6.4.0`
  
- `module load cuda/10.2`

### Compile
- `nvcc q5_single.cu -o q5_single`

- `nvcc q5_double.cu -o q5_double -arch=sm_61`
  
### Run 
- `./q5_single`

- `./q5_double`