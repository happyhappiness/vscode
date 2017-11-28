size_t
ClientSocketContext::lengthToSend(Range<int64_t> const &available)
{
    /*the size of available range can always fit in a size_t type*/
    size_t maximum = (size_t)available.size();

    if (!http->request->range)
        return maximum;

    assert (canPackMoreRanges());

    if (http->range_iter.debt() == -1)
        return maximum;

    assert (http->range_iter.debt() > 0);

    /* TODO this + the last line could be a range intersection calculation */
    if (available.start < http->range_iter.currentSpec()->offset)
        return 0;

    return min(http->range_iter.debt(), (int64_t)maximum);
}