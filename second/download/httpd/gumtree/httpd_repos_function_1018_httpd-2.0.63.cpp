static int cache_tlb_hash(char *key)
{
    unsigned long n;
    char *p;

    n = 0;
    for (p = key; *p != '\0'; p++) {
        n = ((n << 5) + n) ^ (unsigned long)(*p++);
    }

    return n % CACHE_TLB_ROWS;
}