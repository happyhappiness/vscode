bool
HttpHeader::update(HttpHeader const *fresh)
{
    assert(fresh);
    assert(this != fresh);

    // Optimization: Finding whether a header field changed is expensive
    // and probably not worth it except for collapsed revalidation needs.
    if (Config.onoff.collapsed_forwarding && !needUpdate(fresh))
        return false;

    updateWarnings();

    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;

    while ((e = fresh->getEntry(&pos))) {
        /* deny bad guys (ok to check for Http::HdrType::OTHER) here */

        if (skipUpdateHeader(e->id))
            continue;

        if (e->id != Http::HdrType::OTHER)
            delById(e->id);
        else
            delByName(e->name.termedBuf());
    }

    pos = HttpHeaderInitPos;
    while ((e = fresh->getEntry(&pos))) {
        /* deny bad guys (ok to check for Http::HdrType::OTHER) here */

        if (skipUpdateHeader(e->id))
            continue;

        debugs(55, 7, "Updating header '" << Http::HeaderLookupTable.lookup(e->id).name << "' in cached entry");

        addEntry(e->clone());
    }
    return true;
}