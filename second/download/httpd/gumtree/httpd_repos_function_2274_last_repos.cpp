size_t h2_iq_mshift(h2_iqueue *q, int *pint, size_t max)
{
    int i;
    for (i = 0; i < max; ++i) {
        pint[i] = h2_iq_shift(q);
        if (pint[i] == 0) {
            break;
        }
    }
    return i;
}