void
httpHeaderInitModule(void)
{
    /* check that we have enough space for masks */
    assert(8 * sizeof(HttpHeaderMask) >= Http::HdrType::enumEnd_);

    // masks are needed for stats page still
    for (auto h : WholeEnum<Http::HdrType>()) {
        if (Http::HeaderLookupTable.lookup(h).request)
            CBIT_SET(RequestHeadersMask,h);
        if (Http::HeaderLookupTable.lookup(h).reply)
            CBIT_SET(ReplyHeadersMask,h);
    }

    /* header stats initialized by class constructor */
    assert(HttpHeaderStatCount == hoReply + 1);

    /* init dependent modules */
    httpHdrCcInitModule();
    httpHdrScInitModule();

    httpHeaderRegisterWithCacheManager();
}