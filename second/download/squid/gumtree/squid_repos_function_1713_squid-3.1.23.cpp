double
statHistDeltaPctile(const StatHist * A, const StatHist * B, double pctile)
{
    int i;
    int s1 = 0;
    int h = 0;
    int a = 0;
    int b = 0;
    int I = 0;
    int J = A->capacity;
    int K;
    double f;
    int *D = (int *)xcalloc(A->capacity, sizeof(int));
    assert(A->capacity == B->capacity);

    for (i = 0; i < A->capacity; i++) {
        D[i] = B->bins[i] - A->bins[i];
        assert(D[i] >= 0);
    }

    for (i = 0; i < A->capacity; i++)
        s1 += D[i];

    h = int(s1 * pctile);

    for (i = 0; i < A->capacity; i++) {
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

    K = (int) floor(f * (double) (J - I) + I);

    return statHistVal(A, K);
}