static double
statCPUUsage(int minutes)
{
    assert(minutes < N_COUNT_HIST);
    return Math::doublePercent(CountHist[0].cputime - CountHist[minutes].cputime,
                               tvSubDsec(CountHist[minutes].timestamp, CountHist[0].timestamp));
}