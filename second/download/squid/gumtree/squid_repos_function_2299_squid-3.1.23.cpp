void
httpHdrCcUpdateStats(const HttpHdrCc * cc, StatHist * hist)
{
    http_hdr_cc_type c;
    assert(cc);

    for (c = CC_PUBLIC; c < CC_ENUM_END; ++c)
        if (EBIT_TEST(cc->mask, c))
            statHistCount(hist, c);
}