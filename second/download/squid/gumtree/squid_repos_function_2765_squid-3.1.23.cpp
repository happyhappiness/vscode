void
HttpHeader::putSc(HttpHdrSc *sc)
{
    MemBuf mb;
    Packer p;
    assert(sc);
    /* remove old directives if any */
    delById(HDR_SURROGATE_CONTROL);
    /* pack into mb */
    mb.init();
    packerToMemInit(&p, &mb);
    httpHdrScPackInto(sc, &p);
    /* put */
    addEntry(new HttpHeaderEntry(HDR_SURROGATE_CONTROL, NULL, mb.buf));
    /* cleanup */
    packerClean(&p);
    mb.clean();
}