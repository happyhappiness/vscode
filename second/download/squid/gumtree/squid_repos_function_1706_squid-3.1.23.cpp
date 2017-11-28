void
statHistClean(StatHist * H)
{
    xfree(H->bins);
    H->bins = NULL;
}