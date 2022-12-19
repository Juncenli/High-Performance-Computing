## Compile (using AVX)

- `g++ -std=gnu++11 -o floatSinxAVX floatSinxAVX.cpp #SBATCH –constraint=cascadelake -march=native`

## run
- `./floatSinxAVX`

## Compile (not using AVX)

- `g++ -std=gnu++11 -o floatSinx floatSinxAVX.cpp`

## run

- `./floatSinx`