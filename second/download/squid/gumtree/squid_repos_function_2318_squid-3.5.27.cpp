void
recordMemBlobSizeAtDestruct(SBuf::size_type sz)
{
    collectMemBlobDestructTimeStats().count(static_cast<double>(sz));
}