void
statHistIntInit(StatHist * H, int n)
{
    statHistInit(H, n, Null, Null, (double) 0, (double) n - 1);
}