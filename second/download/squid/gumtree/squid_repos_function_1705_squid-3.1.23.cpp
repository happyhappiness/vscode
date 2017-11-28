static void
statHistInit(StatHist * H, int capacity, hbase_f * val_in, hbase_f * val_out, double min, double max)
{
    assert(H);
    assert(capacity > 0);
    assert(val_in && val_out);
    /* check before we divide to get scale */
    assert(val_in(max - min) > 0);
    H->bins = (int *)xcalloc(capacity, sizeof(int));
    H->min = min;
    H->max = max;
    H->capacity = capacity;
    H->scale = capacity / val_in(max - min);
    H->val_in = val_in;
    H->val_out = val_out;

    /* HPUX users: If you get one of the assertions below, please send
     * [at least] the values of all variables involved in the assertions
     * when reporting a bug!
     */

    /* check that functions are valid */
    /* a min value should go into bin[0] */
    assert(statHistBin(H, min) == 0);
    /* a max value should go into the last bin */
    assert(statHistBin(H, max) == H->capacity - 1);
    /* it is hard to test val_out, here is a crude test */
    assert(((int) floor(0.99 + statHistVal(H, 0) - min)) == 0);
}