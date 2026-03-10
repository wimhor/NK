# NK
Code for performing random, uphill, or downhill walks on NK landscapes, or random walks on NKC landscapes where the other species undergoes a random mutation every `s` steps.

This code combines various methods that were used to generate the results in the following publications:
- W. Hordijk and S. A. Kauffman. [Correlation analysis of coupled fitness landscapes](http://onlinelibrary.wiley.com/doi/10.1002/cplx.20092/abstract). _Complexity_ 10(6):41-49, 2005.
- W. Hordijk, S. A. Kauffman and P. F. Stadler. [Average fitness differences on NK landscapes](http://link.springer.com/article/10.1007/s12064-019-00296-0). _Theory in Biosciences_ 139(1):1-7, 2020.

This C++ code is largely based on earlier C code by [Terry Jones](https://github.com/terrycojones/nk-landscapes). It comes without any warranty, but feel free to use it for your own purposes. If you do so, a reference to the [current repo](https://github.com/wimhor/NK) will be appreciated.

## Compile
To compile, go into the `src` directory and type

    make nk

to compile the `nk_walk` program or

    make nkc

to compile the `nkc_walk` program. The executables will be placed in the parent directory.

## Run
To run, go back up to the parent directory and type

    ./nk_walk -help

or

    ./nkc_walk -help
    
to see the list of required and optional program arguments.

## Arguments
Both programs require at least a certain number of arguments, while others are optional.

For the `nk_walk` program, the following arguments are required:
  - `-n N`:     The genome length N (`N>0`).
  - `-k K`:     The number K of epistatic interactions for each gene (`0<=K<N`).

while these are optional (defaults indicated):
  - `-a A`:     The alphabet size A (default=`2`).
  - `-epi E`:   The type E of epistatic interactions: `adj` (default) or `rnd`.
  - `-walk W`:  The type W of walk to perform: `random` (default), `uphill`, or `downhill`.
  - `-len L`:   The length L of a random walk (default=`100`).
  - `-nr Nr`:   The number Nr of walks to perform (default=`100`).
  - `-print P`: Which mutant fitness values P to print: `none` (default), `fitter`, or `all`.
  - `-s S`:     The random seed S (default=`-1`: use current time).
  - `-help`:    Print this help message and exit.

For the `nkc_walk` program, the following arguments are required:
  - `-n N`:     The genome length N (`N>0`).
  - `-k K`:     The number K of epistatic interactions for each gene (`0<=K<N`).
  - `-c C`:     The number C of between-species epistatic interactions (`0<=C<N`).

while these are optional (defaults indicated):
  - `-a A`:     The alphabet size A (default=`2`).
  - `-epi E`:   The type E of epistatic interactions: `adj` (default) or `rnd`.
  - `-s S`:     The random seed S (default=`-1`: use current time).
  - `-len L`:   The length L of the random walk (default=`100`).
  - `-m M`:     The number of steps M after which the other species is mutated (default=`0`).
  - `-help`:    Print this help message and exit.

## Known issues
The program `nkc_walk` currently seems to produce incorrect fitness values for `A>2`. For now it's best to stick with the default `A=2` (i.e., bit strings), until this is fixed.
