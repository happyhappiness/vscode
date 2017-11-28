void
httpHeaderInitModule(void)
{
    int i;
    /* check that we have enough space for masks */
    assert(8 * sizeof(HttpHeaderMask) >= HDR_ENUM_END);
    /* all headers must be described */
    assert(countof(HeadersAttrs) == HDR_ENUM_END);

    if (!Headers)
        Headers = httpHeaderBuildFieldsInfo(HeadersAttrs, HDR_ENUM_END);

    /* create masks */
    httpHeaderMaskInit(&ListHeadersMask, 0);
    httpHeaderCalcMask(&ListHeadersMask, ListHeadersArr, countof(ListHeadersArr));

    httpHeaderMaskInit(&ReplyHeadersMask, 0);
    httpHeaderCalcMask(&ReplyHeadersMask, ReplyHeadersArr, countof(ReplyHeadersArr));
    httpHeaderCalcMask(&ReplyHeadersMask, GeneralHeadersArr, countof(GeneralHeadersArr));
    httpHeaderCalcMask(&ReplyHeadersMask, EntityHeadersArr, countof(EntityHeadersArr));

    httpHeaderMaskInit(&RequestHeadersMask, 0);
    httpHeaderCalcMask(&RequestHeadersMask, RequestHeadersArr, countof(RequestHeadersArr));
    httpHeaderCalcMask(&RequestHeadersMask, GeneralHeadersArr, countof(GeneralHeadersArr));
    httpHeaderCalcMask(&RequestHeadersMask, EntityHeadersArr, countof(EntityHeadersArr));

    httpHeaderMaskInit(&HopByHopHeadersMask, 0);
    httpHeaderCalcMask(&HopByHopHeadersMask, HopByHopHeadersArr, countof(HopByHopHeadersArr));

    /* init header stats */
    assert(HttpHeaderStatCount == hoReply + 1);
    for (i = 0; i < HttpHeaderStatCount; ++i)
        httpHeaderStatInit(HttpHeaderStats + i, HttpHeaderStats[i].label);

    HttpHeaderStats[hoRequest].owner_mask = &RequestHeadersMask;

    HttpHeaderStats[hoReply].owner_mask = &ReplyHeadersMask;

#if USE_HTCP
    HttpHeaderStats[hoHtcpReply].owner_mask = &ReplyHeadersMask;
#endif

    /* init dependent modules */
    httpHdrCcInitModule();
    httpHdrScInitModule();

    httpHeaderRegisterWithCacheManager();
}