int
hashPrime(int n)
{
    int I = sizeof(hash_primes) / sizeof(int);
    int i;
    int best_prime = hash_primes[0];
    double min = fabs(log((double) n) - log((double) hash_primes[0]));
    double d;
    for (i = 0; i < I; i++) {
        d = fabs(log((double) n) - log((double) hash_primes[i]));
        if (d > min)
            continue;
        min = d;
        best_prime = hash_primes[i];
    }
    return best_prime;
}