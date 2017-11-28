void
HttpHeader::putCc(const HttpHdrCc * cc)
{
    MemBuf mb;
    Packer p;
    assert(cc);
    /* remove old directives if any */
    delById(HDR_CACHE_CONTROL);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    httpHdrCcPackInto(cc, &p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_CACHE_CONTROL, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}