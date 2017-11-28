extern double
statByteHitRatio(int minutes)
{
    size_t s;
    size_t c;
#if USE_CACHE_DIGESTS

    size_t cd;
#endif
    /* size_t might be unsigned */
    assert(minutes < N_COUNT_HIST);
    c = CountHist[0].client_http.kbytes_out.kb - CountHist[minutes].client_http.kbytes_out.kb;
    s = CountHist[0].server.all.kbytes_in.kb - CountHist[minutes].server.all.kbytes_in.kb;
#if USE_CACHE_DIGESTS
    /*
     * This ugly hack is here to prevent the user from seeing a
     * negative byte hit ratio.  When we fetch a cache digest from
     * a neighbor, it gets treated like a cache miss because the
     * object is consumed internally.  Thus, we subtract cache
     * digest bytes out before calculating the byte hit ratio.
     */
    cd = CountHist[0].cd.kbytes_recv.kb - CountHist[minutes].cd.kbytes_recv.kb;

    if (s < cd)
        debugs(18, 1, "STRANGE: srv_kbytes=" << s << ", cd_kbytes=" << cd);

    s -= cd;

#endif

    if (c > s)
        return Math::doublePercent(c - s, c);
    else
        return (-1.0 * Math::doublePercent(s - c, c));
}