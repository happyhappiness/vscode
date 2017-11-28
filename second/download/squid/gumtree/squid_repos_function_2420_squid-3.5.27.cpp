HttpHeaderFieldInfo *
httpHeaderBuildFieldsInfo(const HttpHeaderFieldAttrs * attrs, int count)
{
    int i;
    HttpHeaderFieldInfo *table = NULL;
    assert(attrs && count);

    /* allocate space */
    table = new HttpHeaderFieldInfo[count];

    for (i = 0; i < count; ++i) {
        const http_hdr_type id = attrs[i].id;
        HttpHeaderFieldInfo *info = table + id;
        /* sanity checks */
        assert(id >= 0 && id < count);
        assert(attrs[i].name);
        assert(info->id == HDR_ACCEPT && info->type == ftInvalid);  /* was not set before */
        /* copy and init fields */
        info->id = id;
        info->type = attrs[i].type;
        info->name = attrs[i].name;
        assert(info->name.size());
    }

    return table;
}