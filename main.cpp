#include <iostream>
#include <unordered_map>
#include "HashFunction.h"
//#include "LSH.h"
#include <random>
#include <algorithm>
#include <math.h>
#include "SignedRandomProjection.h"
//#include "L2LSH.h"
#include "MCMC.h"
#include "Gaussian.h"
//#pragma once
/* Author: Chen Luo
*  COPYRIGHT PROTECTION
*  Free for research use. 
*  For commercial use, contact:  RICE UNIVERSITY INVENTION & PATENT or the Author.
*/

using namespace std;
//using namespace concurrency;


int main (int argc, char *argv[])
{
    // Generate a sample data here to do experiment.
    // With 0,1 one cluster, 3,4 one cluster
    
    int K = 3;
    int L = 1;
    int dim = 3;
    int N = 100; // Datasize
    int clusnum = 10;
    
    double ** data = new double*[N];
    int * label = new int[N];

    for (int i=0;i<N;i++)
    {
        data[i] = new double[dim];
        Gaussian * gaussian = new Gaussian((double)(i % clusnum), 2, dim);
        data[i] = gaussian->getData();
        //cout << data[i][0] << endl;
     }
     

    /*
    MCMC * mcmc = new MCMC(data, label, N, dim, clusnum, K, L);

    clock_t t1, t2;
    t1 = clock();
 
    //mcmc->EM_GMM(clusnum);
    //mcmc->SM_GMM();
    //mcmc->SDDSSM_GMM();
    mcmc->LSHSM_GMM();

    t2 = clock();

    printf ("It took me %f seconds.\n",((float)t2 - (float)t1)/CLOCKS_PER_SEC);
    return 0;
    */
    
    LSH* lsh = new LSH(K,L);

    L2LSH * l2lsh = new L2LSH(dim, K*L) ;

    for (int j=0; j<N; j++ )
    {
        lsh->add(l2lsh->getHash(data[j], dim), j);
    }

    
    for (int i=0; i<N; i++ )
    {
        cout << "Data Number: " << i << endl;

        // What happened with the hashing here!
        int * candidates = lsh->retrieve(l2lsh->getHash(data[i], dim));
        for (int j=0; j< candidates[0]; j++)
        {
            cout <<candidates[j+2] << "  "; // the top 2 value is nothing!
        }
        cout << endl;
    }
    
    /*
    int* sample = lsh->sample(srp->getHash(data[2], 3)) ;

    printf("%d, %d, %d\n", sample[0], sample[1], sample[2]);

    int range = 1<<lsh->_rangePow;
    
    cout << "range" << range << endl;
    cout << "collision" << srp->getProb(data[2],data[sample[0]], 3) << endl;
    double cp = (1.0 - 1.0/(range))*srp->getProb(data[2],data[sample[0]], 3) + 1.0/(range);

    cout << "cp:" << (1.0 - pow((1.0 - pow(cp,K)),sample[2])) << endl;
    
    double p = (1.0 - pow((1.0 - pow(cp,K)),sample[2]+1))*(1.0/sample[1]);

    cout << "Hello World!, p=" <<p<< "\n" ;
    */
}
