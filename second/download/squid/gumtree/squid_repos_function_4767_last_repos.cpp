StatHist &
collectMemBlobDestructTimeStats()
{
    static StatHist *stats = newStatHist();
    return *stats;
}