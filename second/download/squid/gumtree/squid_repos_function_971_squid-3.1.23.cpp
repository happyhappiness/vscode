const char *
HttpParserHdrBuf(HttpParser *hp)
{
    assert(hp->state == 1);
    assert(hp->hdr_start != -1);
    assert(hp->hdr_end != -1);
    return hp->buf + hp->hdr_start;
}