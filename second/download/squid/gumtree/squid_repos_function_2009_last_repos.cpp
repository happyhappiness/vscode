void
httpHdrCcUpdateStats(const HttpHdrCc * cc, StatHist * hist)
{
    assert(cc);

    for (HttpHdrCcType c = HttpHdrCcType::CC_PUBLIC; c < HttpHdrCcType::CC_ENUM_END; ++c)
        if (cc->isSet(c))
            hist->count(c);
}