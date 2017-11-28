int
TunnelStateData::Connection::bytesWanted(int lowerbound, int upperbound) const
{
#if DELAY_POOLS
    return delayId.bytesWanted(lowerbound, upperbound);
#else

    return upperbound;
#endif
}