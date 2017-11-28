void
httpHdrScTargetUpdateStats(const HttpHdrScTarget * sc, StatHist * hist)
{
    http_hdr_sc_type c;
    assert(sc);

    for (c = SC_NO_STORE; c < SC_ENUM_END; ++c)
        if (EBIT_TEST(sc->mask, c))
            statHistCount(hist, c);
}