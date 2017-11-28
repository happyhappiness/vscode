StatCounters *
snmpStatGet(int minutes)
{
    return &CountHist[minutes];
}