void
HttpHeader::putContRange(const HttpHdrContRange * cr)
{
    MemBuf mb;
    Packer p;
    assert(cr);
    /* remove old directives if any */
    delById(HDR_CONTENT_RANGE);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    httpHdrContRangePackInto(cr, &p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_CONTENT_RANGE, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}