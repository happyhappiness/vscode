static void
httpHeaderStatInit(HttpHeaderStat * hs, const char *label)
{
    assert(hs);
    assert(label);
    memset(hs, 0, sizeof(HttpHeaderStat));
    hs->label = label;
    hs->hdrUCountDistr.enumInit(32);	/* not a real enum */
    hs->fieldTypeDistr.enumInit(HDR_ENUM_END);
    hs->ccTypeDistr.enumInit(CC_ENUM_END);
    hs->scTypeDistr.enumInit(SC_ENUM_END);
}