StatHist &
collectSBufDestructTimeStats()
{
    static StatHist *stats = newStatHist();
    return *stats;
}