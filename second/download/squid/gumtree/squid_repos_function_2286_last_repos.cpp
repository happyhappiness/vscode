void
HttpHeader::putSc(HttpHdrSc *sc)
{
    assert(sc);
    /* remove old directives if any */
    delById(Http::HdrType::SURROGATE_CONTROL);
    /* pack into mb */
    MemBuf mb;
    mb.init();
    sc->packInto(&mb);
    /* put */
    addEntry(new HttpHeaderEntry(Http::HdrType::SURROGATE_CONTROL, NULL, mb.buf));
    /* cleanup */
    mb.clean();
}