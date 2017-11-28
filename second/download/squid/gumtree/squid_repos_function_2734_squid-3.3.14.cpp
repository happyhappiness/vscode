void
HttpHeader::update (HttpHeader const *fresh, HttpHeaderMask const *denied_mask)
{
    const HttpHeaderEntry *e;
    HttpHeaderPos pos = HttpHeaderInitPos;
    assert(fresh);
    assert(this != fresh);

    while ((e = fresh->getEntry(&pos))) {
        /* deny bad guys (ok to check for HDR_OTHER) here */

        if (denied_mask && CBIT_TEST(*denied_mask, e->id))
            continue;

        if (e->id != HDR_OTHER)
            delById(e->id);
        else
            delByName(e->name.termedBuf());
    }

    pos = HttpHeaderInitPos;
    while ((e = fresh->getEntry(&pos))) {
        /* deny bad guys (ok to check for HDR_OTHER) here */

        if (denied_mask && CBIT_TEST(*denied_mask, e->id))
            continue;

        debugs(55, 7, "Updating header '" << HeadersAttrs[e->id].name << "' in cached entry");

        addEntry(e->clone());
    }
}