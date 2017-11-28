extern double
statRequestHitMemoryRatio(int minutes)
{
    assert(minutes < N_COUNT_HIST);
    return Math::doublePercent(CountHist[0].client_http.mem_hits -
                               CountHist[minutes].client_http.mem_hits,
                               CountHist[0].client_http.hits -
                               CountHist[minutes].client_http.hits);
}