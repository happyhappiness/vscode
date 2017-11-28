void
httpHdrCcSetSMaxAge(HttpHdrCc * cc, int s_maxage)
{
    assert(cc);
    cc->s_maxage = s_maxage;

    if (s_maxage >= 0)
        EBIT_SET(cc->mask, CC_S_MAXAGE);
    else
        EBIT_CLR(cc->mask, CC_S_MAXAGE);
}