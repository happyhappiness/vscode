void
Http::Stream::noteSentBodyBytes(size_t bytes)
{
    debugs(33, 7, bytes << " body bytes");
    http->out.offset += bytes;

    if (!http->request->range)
        return;

    if (http->range_iter.debt() != -1) {
        http->range_iter.debt(http->range_iter.debt() - bytes);
        assert (http->range_iter.debt() >= 0);
    }

    /* debt() always stops at -1, below that is a bug */
    assert(http->range_iter.debt() >= -1);
}