unsigned int
LeakFinder::hash(const void *p, unsigned int mod)
{
    return ((unsigned long) p >> 8) % mod;
}