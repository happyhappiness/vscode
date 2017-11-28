void
httpHdrCcDestroy(HttpHdrCc * cc)
{
    assert(cc);

    if (cc->other.defined())
        cc->other.clean();

    memFree(cc, MEM_HTTP_HDR_CC);
}