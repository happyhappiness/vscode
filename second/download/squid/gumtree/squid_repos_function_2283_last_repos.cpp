void
HttpHeader::putCc(const HttpHdrCc * cc)
{
    assert(cc);
    /* remove old directives if any */
    delById(Http::HdrType::CACHE_CONTROL);
    /* pack into mb */
    MemBuf mb;
    mb.init();
    cc->packInto(&mb);
    /* put */
    addEntry(new HttpHeaderEntry(Http::HdrType::CACHE_CONTROL, NULL, mb.buf));
    /* cleanup */
    mb.clean();
}