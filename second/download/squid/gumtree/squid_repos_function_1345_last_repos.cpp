int
stat5minClientRequests(void)
{
    assert(N_COUNT_HIST > 5);
    return statCounter.client_http.requests - CountHist[5].client_http.requests;
}