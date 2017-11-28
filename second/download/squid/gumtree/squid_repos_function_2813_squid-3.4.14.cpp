void
HttpHeader::putRange(const HttpHdrRange * range)
{
    MemBuf mb;
    Packer p;
    assert(range);
    /* remove old directives if any */
    delById(HDR_RANGE);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    range->packInto(&p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_RANGE, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}