int
VectorPool::Id::bytesWanted (int min, int max) const
{
    return theVector->buckets.values[theIndex].bytesWanted (min, max);
}