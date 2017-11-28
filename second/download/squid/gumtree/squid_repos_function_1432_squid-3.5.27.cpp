void
SBuf::reserveCapacity(size_type minCapacity)
{
    Must(minCapacity <= maxSize);
    cow(minCapacity);
}