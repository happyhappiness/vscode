int
DelayVector::Id::bytesWanted (int minimum, int maximum) const
{
    int nbytes = maximum;
    const_iterator pos = ids.begin();

    while (pos != ids.end()) {
        nbytes = min (nbytes, (*pos)->bytesWanted(minimum, nbytes));
        ++pos;
    }

    nbytes = max(minimum, nbytes);
    return nbytes;
}