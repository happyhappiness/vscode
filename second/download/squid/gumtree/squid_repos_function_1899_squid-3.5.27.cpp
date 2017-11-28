double
StatHist::deltaPctile(const StatHist & B, double pctile) const
{
    unsigned int i;
    bins_type s1 = 0;
    bins_type h = 0;
    bins_type a = 0;
    bins_type b = 0;
    unsigned int I = 0;
    unsigned int J = capacity_;
    unsigned int K;
    double f;

    assert(capacity_ == B.capacity_);

    int *D = static_cast<int *>(xcalloc(capacity_, sizeof(int)));

    for (i = 0; i < capacity_; ++i) {
        D[i] = B.bins[i] - bins[i];
        assert(D[i] >= 0);
    }

    for (i = 0; i < capacity_; ++i)
        s1 += D[i];

    h = int(s1 * pctile);

    for (i = 0; i < capacity_; ++i) {
        J = i;
        b += D[J];

        if (a <= h && h <= b)
            break;

        I = i;

        a += D[I];
    }

    xfree(D);

    if (s1 == 0)
        return 0.0;

    if (a > h)
        return 0.0;

    if (a >= b)
        return 0.0;

    if (I >= J)
        return 0.0;

    f = (h - a) / (b - a);

    K = (unsigned int) floor(f * (double) (J - I) + I);

    return val(K);
}