HttpHdrContRange *
HttpHeader::getContRange() const
{
    HttpHdrContRange *cr = NULL;
    HttpHeaderEntry *e;

    if ((e = findEntry(HDR_CONTENT_RANGE))) {
        cr = httpHdrContRangeParseCreate(e->value.termedBuf());
        httpHeaderNoteParsedEntry(e->id, e->value, !cr);
    }

    return cr;
}