#!/bin/sh

export LIBAROMA_GCC="gcc"
export LIBAROMA_GPP="g++"

# export LIBAROMA_CFLAGS="-O3 -fopenmp -DLIBAROMA_CONFIG_OPENMP=1 -DLIBAROMA_CONFIG_DEBUG_TRACE=0"
export LIBAROMA_CFLAGS="-O3 -ftree-vectorize -fprefetch-loop-arrays -funsafe-math-optimizations -fopenmp -DLIBAROMA_CONFIG_OPENMP=1 -DLIBAROMA_CONFIG_NOJPEG=1 -DLIBAROMA_CONFIG_DEBUG_TRACE=0"
export LIBAROMA_DEBUG_CFLAGS="-ggdb -fopenmp -DLIBAROMA_CONFIG_OPENMP=1 -DLIBAROMA_CONFIG_DEBUG_TRACE=0"

export LIBAROMA_CONFIG_DEBUG="4"
export LIBAROMA_CONFIG_DEBUG_FILE="1"
export LIBAROMA_CONFIG_DEBUG_MEMORY="0"
export LIBAROMA_CONFIG_COMPILER_MESSAGE="1"
export LIBAROMA_CONFIG_SHMEMFB="0"

bash
