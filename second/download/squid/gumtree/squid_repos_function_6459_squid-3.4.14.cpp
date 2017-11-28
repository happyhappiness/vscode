void *
Ipc::Mem::Segment::reserve(size_t chunkSize)
{
    Must(theMem);
    // check for overflows
    // chunkSize >= 0 may result in warnings on systems where off_t is unsigned
    assert(!chunkSize || static_cast<off_t>(chunkSize) > 0);
    assert(static_cast<off_t>(chunkSize) <= theSize);
    assert(theReserved <= theSize - static_cast<off_t>(chunkSize));
    void *result = reinterpret_cast<char*>(theMem) + theReserved;
    theReserved += chunkSize;
    return result;
}