## Using GPUs with PyTorch - Discovery

### Using P100

- `srun --partition=gpu --nodes=1 --pty --gres=gpu:p100:1 --ntasks=1 --mem=4GB --time=04:00:00 /bin/bash`

### Using K80
- `srun --partition=gpu --nodes=1 --pty --gres=gpu:k80:1 --ntasks=1 --mem=4GB --time=04:00:00 /bin/bash`

### Load Modules
- `module load anaconda3/2022.01`
- `module load cuda/11.1`
  
### Activate environment
- `source activate pytorch_env_training`

### Check Pytorch
- `python -c'import torch; print(torch.cuda.is_available())'`
The reason for torch.cuda.is_available() resulting False is the incompatibility between the versions of pytorch and cudatoolkit.

### Training GoogleNet using cifar10
- `python cifar10-googlenet.py`

### Training GoogleNet using MNIST
- `python MNIST-googlenet.py`

### Training GoogleNet using KMNIST
- `python KMNIST-googlenet.py`

### Training RestNet18 using cifar10
- `python cifar10-resnet18.py`

### Training RestNet18 using MNIST
- `python MNIST-resnet18.py`

### Training RestNet18 using KMNIST
- `python KMNIST-resnet18.py`