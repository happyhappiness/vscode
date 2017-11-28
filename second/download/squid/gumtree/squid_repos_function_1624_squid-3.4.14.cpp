int
ClassCHostPool::Id::bytesWanted (int min, int max) const
{
    return theClassCHost->buckets.values[theNet].individuals.values[theHost].bytesWanted (min, max);
}