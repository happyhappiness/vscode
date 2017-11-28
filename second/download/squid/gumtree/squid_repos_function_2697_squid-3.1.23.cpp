void
TunnelStateData::Connection::bytesIn(int const &count)
{
#if DELAY_POOLS
    delayId.bytesIn(count);
#endif

    len += count;
}