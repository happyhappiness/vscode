HttpHdrContRange *
HttpHeader::getContRange() const
{
    HttpHdrContRange *cr = NULL;
    HttpHeaderEntry *e;

    if ((e = findEntry(Http::HdrType::CONTENT_RANGE))) {
        cr = httpHdrContRangeParseCreate(e->value.termedBuf());
        httpHeaderNoteParsedEntry(e->id, e->value, !cr);
    }

    return cr;
}