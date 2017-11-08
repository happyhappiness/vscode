static int rewrite_rand(int l, int h)
{
    rewrite_rand_init();

    /* Get [0,1) and then scale to the appropriate range. Note that using
     * a floating point value ensures that we use all bits of the rand()
     * result. Doing an integer modulus would only use the lower-order bits
     * which may not be as uniformly random.
     */
    return (int)(((double)(rand() % RAND_MAX) / RAND_MAX) * (h - l + 1) + l);
}