static int get_b_rand(void)
{
    static int ph = 32;         /* More bits than we will ever use */
    static apr_uint32_t randseq;
    if (ph > 31) {              /* Num bits in return of rand() */
        ph = 0;
        randseq = (apr_uint32_t) rand();
    }
    ph++;
    return ((randseq & (1 << (ph - 1))) >> (ph - 1));
}