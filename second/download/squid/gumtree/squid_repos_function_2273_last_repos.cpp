bool
HttpHeader::hasNamed(const char *name, int namelen, String *result) const
{
    Http::HdrType id;
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;

    assert(name);

    /* First try the quick path */
    id = Http::HeaderLookupTable.lookup(name,namelen).id;

    if (id != Http::HdrType::BAD_HDR) {
        if (getByIdIfPresent(id, result))
            return true;
    }

    /* Sorry, an unknown header name. Do linear search */
    bool found = false;
    while ((e = getEntry(&pos))) {
        if (e->id == Http::HdrType::OTHER && e->name.size() == static_cast<String::size_type>(namelen) && e->name.caseCmp(name, namelen) == 0) {
            found = true;
            if (!result)
                break;
            strListAdd(result, e->value.termedBuf(), ',');
        }
    }

    return found;
}