/*
** nk_walk.cpp: Main routine for performing various types of walks on an NK-landscape.
**
** Wim Hordijk   Last modified: 15 December 2020
*/

#include "NK.h"
#include "Random.h"
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

/*
** Constant values.
*/

static const int RND_WALK=1, UPHILL=2, DOWNHILL=3, NONE=1, FITTER=2, ALL=3;

/*
** Global vars.
**
** N:       The length of the genomes.
** K:       The number of epistatic interactions.
** epi:     The type of epistatic interactions (adjacent or random).
** seed:    The seed value for the random number generator.
** walk:    The type of walk to perform (random, uphill, or downhill).
** len:     The length of the walk (if a random walk).
** nrWalks: The number of walks to perform.
** prnt:    The mutant fitness values to print (none, fitter, or all).
** nk:      A pointer to an NK-landscape.
** rnd:     A pointer to a random number generator.
*/

int           N, K, epi, seed, walk, len, nrWalks, prnt;
Random       *rnd;
NK_Landscape *nk;


/*
** Function prototypes.
*/

int GetArguments (int argc, char **argv);
int performWalk  ();


/*
** main: Main routine of the program.
**
** Parameters:
**   - argc: The number of arguments to the program.
**   - argv: A pointer to the list of arguments.
**
** Returns:
**   If everything went fine: 0.
**   Otherwise:               1.
*/

int main (int argc, char **argv)
{
  int status, i;

  status = 0;

  /*
  ** Get and check the arguments.
  */
  if (GetArguments (argc, argv) == -1)
  {
    status = 1;
    goto End_of_Routine;
  }

  /*
  ** Create an NK-landscape.
  */
  nk = new NK_Landscape (N, K, epi, 2, seed);
  //nk->Test ();
  if (!nk->init_OK)
  {
    status = 1;
    cerr << "Could not create NK-landscape." << endl;
    goto End_of_Routine;
  }

  /*
  ** Create a random number generator for the walks.
  */
  rnd = new Random ();
  rnd->SetSeed (-1);

  /*
  ** Perform the walks.
  */
  for (i = 1; i <= nrWalks; i++)
  {
    cout << "Walk " << i << endl;
    if (performWalk () == -1)
    {
      status = 1;
      goto End_of_Routine;
    }
    cout << endl;
  }

  /*
  ** Clean up after use...
  */
  delete nk;
  delete rnd;

 End_of_Routine:
  /*
  ** return the status.
  */
  return (status);
}


/*
** GetArguments: Get and check the command line arguments.
**
** Parameters:
**   - argc: The number of arguments to the program.
**   - argv: A pointer to the list of arguments.
** 
** Returns:
**   If everything went fine:  0.
**   Otherwise:               -1.
*/

int GetArguments (int argc, char **argv)
{
  int status, i;

  status = 0;

  /*
  ** Set defaults.
  */
  N = -1;
  K = -1;
  epi = NK_Landscape::ADJ;
  seed = -1;
  walk = RND_WALK;
  len = 100;
  nrWalks = 100;
  prnt = NONE;

  /*
  ** Get and check all arguments.
  */
  i = 1;
  while (i < argc)
  {
    if (strcmp (argv[i], "-N") == 0)
    {
      if ((sscanf (argv[++i], "%d", &N) != 1) || (N < 2))
      {
	status = -1;
	cerr << "Invalid value for N: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-K") == 0)
    {
      if ((sscanf (argv[++i], "%d", &K) != 1) || (K < 0) || (K >= N))
      {
	status = -1;
	cerr << "Invalid value for K: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-epi") == 0)
    {
      if (strcmp (argv[++i], "adj") == 0)
      {
	epi = NK_Landscape::ADJ;
      }
      else if (strcmp (argv[i], "rnd") == 0)
      {
	epi = NK_Landscape::RND;
      }
      else
      {
	status = -1;
	cerr << "Unknown type of epistatic interactions: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-s") == 0)
    {
      if (sscanf (argv[++i], "%d", &seed) != 1)
      {
	status = -1;
	cerr << "Invalid value for seed: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-walk") == 0)
    {
      if (strcmp (argv[++i], "random") == 0)
      {
	walk = RND_WALK;
      }
      else if (strcmp (argv[i], "uphill") == 0)
      {
	walk = UPHILL;
      }
      else if (strcmp (argv[i], "downhill") == 0)
      {
	walk = DOWNHILL;
      }
      else
      {
	status = -1;
	cerr << "Unknown type of walk: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-len") == 0)
    {
      if ((sscanf (argv[++i], "%d", &len) != 1) || (len < 1))
      {
	status = -1;
	cerr << "Invalid value for len: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-nr") == 0)
    {
      if ((sscanf (argv[++i], "%d", &nrWalks) != 1) || (nrWalks < 1))
      {
	status = -1;
	cerr << "Invalid value for nrWalks: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-print") == 0)
    {
      if (strcmp (argv[++i], "none") == 0)
      {
	prnt = NONE;
      }
      else if (strcmp (argv[i], "fitter") == 0)
      {
	prnt = FITTER;
      }
      else if (strcmp (argv[i], "all") == 0)
      {
	prnt = ALL;
      }
      else
      {
	status = -1;
	cerr << "Unknown type of walk: " << argv[i] << endl;
	goto End_of_Routine;
      }
      i++;
    }
    else if (strcmp (argv[i], "-help") == 0)
    {
      cout << argv[0] << " -N <N> -K <K> [-epi <epi>] [-walk <walk>] [-len <len>] [-nr <nr>]"
	   << " [-print <print>] [-s <seed>] [-help]" << endl
	   << endl
	   << "  N:     The genome length." << endl
	   << "  K:     The number of epistatic interactions (0<=K<N)."
	   << endl
	   << "  epi:   The type of epistatic interactions ('adj' (default)"
	   << " or 'rnd')." << endl
	   << "  walk:  The type of walk to perform ('random' (default), 'uphill', or 'downhill')"
	   << endl
	   << "  len:   The length of the walk (only considered if the walk type is 'random')."
	   << endl
	   << "  nr:    The number of walks to perform (default=100)." << endl
	   << "  print: Print mutant fitness values ('none' (default), 'fitter', or 'all')."
	   << endl
	   << "  seed:  The seed value for the landscape (default=-1)."
	   << endl
	   << "  help:  Print out this message and exit." << endl;
      status = -1;
      goto End_of_Routine;
    }
    else
    {
      status = -1;
      cerr << "Unknow option " << argv[i] << endl;
      goto End_of_Routine;
    }
  }

  /*
  ** Make sure the user has set at least the N and K values.
  */
  if ((N < 0) || (K < 0))
  {
    status = -1;
    cerr << "Expecting at least the -N and -K options..." << endl;
    goto End_of_Routine;
  }

 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** performWalk: Perform a walk on the landscape and print out the fitness values
**              of each point and all its one-bit mutants.
**
** Returns:
**   If everything went fine:  0.
**   Otherwise:               -1.
*/

int performWalk ()
{
  int    status, *genome, i, l, *mutant, nrMutants, rndMutant;
  double fitness, mutFitness;

  status = 0;

  /*
  ** Allocate the necessary memory.
  */
  genome = new int[N];
  mutant = new int[N];
  
  /*
  ** Create a random genome.
  */
  for (i = 0; i < N; i++)
  {
    genome[i] = rnd->Unif (2);
  }
  nrMutants = 1;
  
  /*
  ** Perform a walk.
  **
  ** Random.
  */
  if (walk == RND_WALK)
  {
    for (l = 0; l < len; l++)
    {
      /*
      ** Calculate the fitness of the current genome and all its one-bit mutants,
      ** and keep track of the fitter mutants.
      */
      fitness = nk->Fitness (genome);
      cout << fitness << " ";
      nrMutants = 0;
      for (i = 0; i < N; i++)
      {
	genome[i] = 1 - genome[i];
	mutFitness = nk->Fitness (genome);
	if (prnt == ALL)
	{
	  cout << mutFitness << " ";
	}
	genome[i] = 1 - genome[i];
	if (mutFitness > fitness)
	{
	  mutant[nrMutants] = i;
	  nrMutants++;
	  if (prnt == FITTER)
	  {
	    cout << mutFitness << " ";
	  }
	}
      }
      cout << endl;
      /*
      ** Pick a random mutant.
      */
      i = rnd->Unif (N);
      genome[i] = 1 - genome[i];
    }
  }
  else if (walk == UPHILL)
  {
    while (nrMutants > 0)
    {
      /*
      ** Calculate the fitness of the current genome and all its one-bit mutants,
      ** and keep track of the fitter mutants.
      */
      fitness = nk->Fitness (genome);
      cout << fitness << " ";
      nrMutants = 0;
      for (i = 0; i < N; i++)
      {
	genome[i] = 1 - genome[i];
	mutFitness = nk->Fitness (genome);
	if (prnt == ALL)
	{
	  cout << mutFitness << " ";
	}
	genome[i] = 1 - genome[i];
	if (mutFitness > fitness)
	{
	  mutant[nrMutants] = i;
	  nrMutants++;
	  if (prnt == FITTER)
	  {
	    cout << mutFitness << " ";
	  }
	}
      }
      cout << endl;
      /*
      ** Pick a random fitter mutant.
      */
      if (nrMutants > 0)
      {
	rndMutant = rnd->Unif (nrMutants);
	i = mutant[rndMutant];
	genome[i] = 1 - genome[i];
      }
    }
  }
  else if (walk == DOWNHILL)
  {
    while (nrMutants > 0)
    {
      /*
      ** Calculate the fitness of the current genome and all its one-bit mutants,
      ** and keep track of the less fit mutants.
      */
      fitness = nk->Fitness (genome);
      cout << fitness << " ";
      nrMutants = 0;
      for (i = 0; i < N; i++)
      {
	genome[i] = 1 - genome[i];
	mutFitness = nk->Fitness (genome);
	if (prnt == ALL)
	{
	  cout << mutFitness << " ";
	}
	genome[i] = 1 - genome[i];
	if (mutFitness < fitness)
	{
	  mutant[nrMutants] = i;
	  nrMutants++;
	  if (prnt == FITTER)
	  {
	    cout << mutFitness << " ";
	  }
	}
      }
      cout << endl;
      /*
      ** Pick a random less fit mutant.
      */
      if (nrMutants > 0)
      {
	rndMutant = rnd->Unif (nrMutants);
	i = mutant[rndMutant];
	genome[i] = 1 - genome[i];
      }
    }
  }
  
  /*
  ** Free the allocated memory.
  */
  delete genome;
  delete mutant;
  
 End_of_Routine:
  /*
  ** Return the status.
  */
  return (status);
}


/*
** EOF: nk_walk.cpp
*/
