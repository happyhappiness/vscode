bool
ClassCHostPool::keyAllocated (unsigned char const key) const
{
    return buckets.indexUsed(buckets.findKeyIndex (key));
}