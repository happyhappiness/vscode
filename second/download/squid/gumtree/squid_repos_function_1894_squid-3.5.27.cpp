void
StatHist::count(double v)
{
    if (bins==NULL) //do not count before initialization or after destruction
        return;
    const unsigned int bin = findBin(v);
    ++bins[bin];
}