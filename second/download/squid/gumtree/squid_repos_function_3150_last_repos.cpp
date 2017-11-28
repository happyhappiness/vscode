const HttpHdrRangeSpec *
HttpHdrRangeIter::currentSpec() const
{
    if (pos != end)
        return *pos;

    return NULL;
}