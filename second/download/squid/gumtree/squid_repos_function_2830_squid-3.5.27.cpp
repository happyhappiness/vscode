const char *
HttpHeader::getStr(http_hdr_type id) const
{
    HttpHeaderEntry *e;
    assert_eid(id);
    assert(Headers[id].type == ftStr);  /* must be of an appropriate type */

    if ((e = findEntry(id))) {
        httpHeaderNoteParsedEntry(e->id, e->value, 0);  /* no errors are possible */
        return e->value.termedBuf();
    }

    return NULL;
}