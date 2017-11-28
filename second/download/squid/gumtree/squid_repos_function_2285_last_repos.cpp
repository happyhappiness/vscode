void
HttpHeader::putRange(const HttpHdrRange * range)
{
    assert(range);
    /* remove old directives if any */
    delById(Http::HdrType::RANGE);
    /* pack into mb */
    MemBuf mb;
    mb.init();
    range->packInto(&mb);
    /* put */
    addEntry(new HttpHeaderEntry(Http::HdrType::RANGE, NULL, mb.buf));
    /* cleanup */
    mb.clean();
}