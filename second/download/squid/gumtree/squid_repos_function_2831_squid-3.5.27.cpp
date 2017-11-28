const char *
HttpHeader::getLastStr(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */

    if ((e = findLastEntry(id))) {
        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
        return e->value.termedBuf();
    }

    return NULL;
}