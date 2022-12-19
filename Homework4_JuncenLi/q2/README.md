## Question Q2 a

## Compile 2Nodes and read the output

- `module load gcc/10.1.0`
  
- `module load openmpi`
  
- `mpicc q2a.c -o q2a_2nodes`
  
- `sbatch q2a_2nodes.script`

- `more q2a_2nodes.out`
  



## Compile 4Nodes and read the output

- `module load gcc/10.1.0`
  
- `module load openmpi`
  
- `mpicc q2a.c -o q2a_4nodes`
  
- `sbatch q2a_4nodes.script`

- `more q2a_4nodes.out`
  

## Using test code

- `module load gcc/10.1.0`
  
- `module load openmpi`
  
- `mpicc q2aTest.c -o q2aTest`
  
- `sbatch q2aTest.script`

- `more test_q2a_2nodes.out`



---

## Question Q2 b



## Compile 2Nodes and read the output

- `module load gcc/10.1.0`
  
- `module load openmpi`
  
- `mpicc q2b.c -o q2b_2nodes`
  
- `sbatch q2b_2nodes.script`

- `more q2b_2nodes.out`
  



## Compile 4Nodes and read the output

- `module load gcc/10.1.0`
  
- `module load openmpi`
  
- `mpicc q2b.c -o q2b_4nodes`
  
- `sbatch q2b_4nodes.script`

- `more q2b_4nodes.out`