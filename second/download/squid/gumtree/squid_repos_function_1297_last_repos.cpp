void
ClassCHostPool::Id::bytesIn(int qty)
{
    theClassCHost->buckets.values[theNet].individuals.values[theHost].bytesIn (qty);
}