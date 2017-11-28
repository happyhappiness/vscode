bool
Store::Disk::objectSizeIsAcceptable(int64_t objsize) const
{
    // need either the expected or the already accumulated object size
    assert(objsize >= 0);
    return minObjectSize() <= objsize && objsize <= maxObjectSize();
}