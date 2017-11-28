extern double
statRequestHitRatio(int minutes)
{
    assert(minutes < N_COUNT_HIST);
    return Math::doublePercent(CountHist[0].client_http.hits -
                               CountHist[minutes].client_http.hits,
                               CountHist[0].client_http.requests -
                               CountHist[minutes].client_http.requests);
}