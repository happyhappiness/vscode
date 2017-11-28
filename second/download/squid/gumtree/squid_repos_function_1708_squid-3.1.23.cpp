void
statHistSafeCopy(StatHist * Dest, const StatHist * Orig)
{
    assert(Dest && Orig);
    assert(Dest->bins);

    if (Dest->capacity == Orig->capacity)
        statHistCopy(Dest, Orig);
}