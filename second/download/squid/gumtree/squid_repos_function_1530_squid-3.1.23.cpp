void
VectorPool::Id::bytesIn(int qty)
{
    theVector->buckets.values[theIndex].bytesIn (qty);
}