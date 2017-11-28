String
HttpHeader::getByName(const char *name) const
{
    http_hdr_type id;
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;

    assert(name);

    /* First try the quick path */
    id = httpHeaderIdByNameDef(name, strlen(name));

    if (id != -1)
        return getStrOrList(id);

    String result;

    /* Sorry, an unknown header name. Do linear search */
    while ((e = getEntry(&pos))) {
        if (e->id == HDR_OTHER && e->name.caseCmp(name) == 0) {
            strListAdd(&result, e->value.termedBuf(), ',');
        }
    }

    return result;
}