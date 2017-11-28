const HttpHdrRangeSpec *
HttpHdrRangeIter::currentSpec() const
{
    if (pos.incrementable())
        return *pos;

    return NULL;
}