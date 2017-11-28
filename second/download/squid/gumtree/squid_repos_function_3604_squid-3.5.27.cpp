bool
ClientSocketContext::canPackMoreRanges() const
{
    /** first update iterator "i" if needed */

    if (!http->range_iter.debt()) {
        debugs(33, 5, HERE << "At end of current range spec for " << clientConnection);

        if (http->range_iter.pos != http->range_iter.end)
            ++http->range_iter.pos;

        http->range_iter.updateSpec();
    }

    assert(!http->range_iter.debt() == !http->range_iter.currentSpec());

    /* paranoid sync condition */
    /* continue condition: need_more_data */
    debugs(33, 5, "ClientSocketContext::canPackMoreRanges: returning " << (http->range_iter.currentSpec() ? true : false));
    return http->range_iter.currentSpec() ? true : false;
}