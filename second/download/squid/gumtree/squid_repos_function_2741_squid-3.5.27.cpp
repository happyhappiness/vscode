void
TunnelStateData::Connection::bytesIn(int const &count)
{
    debugs(26, 3, HERE << "len=" << len << " + count=" << count);
#if USE_DELAY_POOLS
    delayId.bytesIn(count);
#endif

    len += count;
}