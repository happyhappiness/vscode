static void
htcpFreeDetail(htcpDetail * d)
{
    htcpDetailPool->freeOne(d);
}