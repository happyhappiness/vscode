bool
HttpHeader::getByNameIfPresent(const char *name, String &result) const
{
    http_hdr_type id;
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;

    assert(name);

    /* First try the quick path */
    id = httpHeaderIdByNameDef(name, strlen(name));

    if (id != -1) {
        if (!has(id))
            return false;
        result = getStrOrList(id);
        return true;
    }

    /* Sorry, an unknown header name. Do linear search */
    bool found = false;
    while ((e = getEntry(&pos))) {
        if (e->id == HDR_OTHER && e->name.caseCmp(name) == 0) {
            found = true;
            strListAdd(&result, e->value.termedBuf(), ',');
        }
    }

    return found;
}