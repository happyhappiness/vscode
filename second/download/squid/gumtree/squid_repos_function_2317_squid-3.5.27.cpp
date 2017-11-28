void
recordSBufSizeAtDestruct(SBuf::size_type sz)
{
    collectSBufDestructTimeStats().count(static_cast<double>(sz));
}