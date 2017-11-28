extern double
statRequestHitDiskRatio(int minutes)
{
    assert(minutes < N_COUNT_HIST);
    return Math::doublePercent(CountHist[0].client_http.disk_hits -
                               CountHist[minutes].client_http.disk_hits,
                               CountHist[0].client_http.hits -
                               CountHist[minutes].client_http.hits);
}