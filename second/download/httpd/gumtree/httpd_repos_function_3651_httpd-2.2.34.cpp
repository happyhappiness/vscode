static int get_b_rand(void)
{
    static int ph = 32;         /* More bits than we will ever use */
    static int randseq;
    if (ph > 31) {              /* Num bits in return of rand() */
        ph = 0;
        randseq = rand();
    }
    return randseq & (1 << ph++);
}