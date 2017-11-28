static int
statHistBin(const StatHist * H, double v)
{
    int bin;
#if BROKEN_STAT_HIST_BIN

    return 0;
    /* NOTREACHED */
#endif

    v -= H->min;		/* offset */

    if (v <= 0.0)		/* too small */
        return 0;

    bin = (int) floor(H->scale * H->val_in(v) + 0.5);

    if (bin < 0)		/* should not happen */
        bin = 0;

    if (bin >= H->capacity)	/* too big */
        bin = H->capacity - 1;

    return bin;
}