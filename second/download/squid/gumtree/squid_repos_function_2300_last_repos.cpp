TimeOrTag
HttpHeader::getTimeOrTag(Http::HdrType id) const
{
    TimeOrTag tot;
    HttpHeaderEntry *e;
    assert(Http::HeaderLookupTable.lookup(id).type == Http::HdrFieldType::ftDate_1123_or_ETag);    /* must be of an appropriate type */
    memset(&tot, 0, sizeof(tot));

    if ((e = findEntry(id))) {
        const char *str = e->value.termedBuf();
        /* try as an ETag */

        if (etagParseInit(&tot.tag, str)) {
            tot.valid = tot.tag.str != NULL;
            tot.time = -1;
        } else {
            /* or maybe it is time? */
            tot.time = parse_rfc1123(str);
            tot.valid = tot.time >= 0;
            tot.tag.str = NULL;
        }
    }

    assert(tot.time < 0 || !tot.tag.str);   /* paranoid */
    return tot;
}