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
    
to see a list of expected and optional program arguments.

## Arguments
Both programs require at least a certain number of arguments, while others are optional.

For the `nk_walk` program, the following values are required:
  - `N`:     The genome length.
  - `K`:     The number of epistatic interactions (`0<=K<N`).

while these are optional (defaults indicated):
  - `A`:     The alphabet size (default=`2`).
  - `epi`:   The type of epistatic interactions (`adj` (default) or `rnd`).
  - `walk`:  The type of walk to perform (`random` (default), `uphill`, or `downhill`)
  - `len`:   The length of the walk (only considered if the walk type is `random`).
  - `nr`:    The number of walks to perform (default=`100`).
  - `print`: Print mutant fitness values (`none` (default), `fitter`, or `all`).
  - `seed`:  The seed value for the landscape (default=`-1`).

For the `nkc_walk` program, the following values are required:
  - `N`:     The genome length.
  - `K`:     The number of epistatic interactions (`0<=K<N`).
  - `C`:     The number of between-species epistatic interactions (`0<=C<=N`).

while these are optional (defaults indicated):
  - `A`:     The alphabet size (default=`2`).
  - `epi`:   The type of epistatic interactions (`adj` (default) or `rnd`).
  - `seed`:  The seed value for the landscape (default=`-1`).
  - `T`:     The number of steps in the random walk (default=`10000`).
  - `s_mut`: The number of steps after which the other species is mutated (default=`0`).

## Known issues
The program `nkc_walk` currently seems to produce incorrect fitness values for `A>2`. If I find the time I'll look into this, but for now it's best to stick to `A=2` (i.e., bit strings).
