void
HttpHeader::putContRange(const HttpHdrContRange * cr)
{
    assert(cr);
    /* remove old directives if any */
    delById(Http::HdrType::CONTENT_RANGE);
    /* pack into mb */
    MemBuf mb;
    mb.init();
    httpHdrContRangePackInto(cr, &mb);
    /* put */
    addEntry(new HttpHeaderEntry(Http::HdrType::CONTENT_RANGE, NULL, mb.buf));
    /* cleanup */
    mb.clean();
}