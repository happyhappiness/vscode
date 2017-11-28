static void
htcpFreeDetail(htcpDetail * d)
{
    htcpDetailPool->free(d);
}