HttpHeaderEntry *
HttpHeaderEntry::parse(const char *field_start, const char *field_end)
{
    /* note: name_start == field_start */
    const char *name_end = (const char *)memchr(field_start, ':', field_end - field_start);
    int name_len = name_end ? name_end - field_start :0;
    const char *value_start = field_start + name_len + 1;   /* skip ':' */
    /* note: value_end == field_end */

    ++ HeaderEntryParsedCount;

    /* do we have a valid field name within this field? */

    if (!name_len || name_end > field_end)
        return NULL;

    if (name_len > 65534) {
        /* String must be LESS THAN 64K and it adds a terminating NULL */
        debugs(55, DBG_IMPORTANT, "WARNING: ignoring header name of " << name_len << " bytes");
        return NULL;
    }

    if (Config.onoff.relaxed_header_parser && xisspace(field_start[name_len - 1])) {
        debugs(55, Config.onoff.relaxed_header_parser <= 0 ? 1 : 2,
               "NOTICE: Whitespace after header name in '" << getStringPrefix(field_start, field_end) << "'");

        while (name_len > 0 && xisspace(field_start[name_len - 1]))
            --name_len;

        if (!name_len)
            return NULL;
    }

    /* now we know we can parse it */

    debugs(55, 9, "parsing HttpHeaderEntry: near '" <<  getStringPrefix(field_start, field_end) << "'");

    /* is it a "known" field? */
    http_hdr_type id = httpHeaderIdByName(field_start, name_len, Headers, HDR_ENUM_END);

    String name;

    String value;

    if (id < 0)
        id = HDR_OTHER;

    assert_eid(id);

    /* set field name */
    if (id == HDR_OTHER)
        name.limitInit(field_start, name_len);
    else
        name = Headers[id].name;

    /* trim field value */
    while (value_start < field_end && xisspace(*value_start))
        ++value_start;

    while (value_start < field_end && xisspace(field_end[-1]))
        --field_end;

    if (field_end - value_start > 65534) {
        /* String must be LESS THAN 64K and it adds a terminating NULL */
        debugs(55, DBG_IMPORTANT, "WARNING: ignoring '" << name << "' header of " << (field_end - value_start) << " bytes");

        if (id == HDR_OTHER)
            name.clean();

        return NULL;
    }

    /* set field value */
    value.limitInit(value_start, field_end - value_start);

    ++ Headers[id].stat.seenCount;

    debugs(55, 9, "parsed HttpHeaderEntry: '" << name << ": " << value << "'");

    return new HttpHeaderEntry(id, name.termedBuf(), value.termedBuf());
}