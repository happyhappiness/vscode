void
StatHist::count(double val)
{
    if (bins==NULL) //do not count before initialization or after destruction
        return;
    const unsigned int bin = findBin(val);
    ++bins[bin];
}