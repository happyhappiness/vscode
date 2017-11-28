void
HttpHeader::packInto(Packer * p, bool mask_sensitive_info) const
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    const HttpHeaderEntry *e;
    assert(p);
    debugs(55, 7, "packing hdr: (" << this << ")");
    /* pack all entries one by one */
    while ((e = getEntry(&pos))) {
        if (!mask_sensitive_info) {
            e->packInto(p);
            continue;
        }
        switch (e->id) {
        case HDR_AUTHORIZATION:
        case HDR_PROXY_AUTHORIZATION:
            packerAppend(p, e->name.rawBuf(), e->name.size());
            packerAppend(p, ": ** NOT DISPLAYED **\r\n", 23);
            break;
        default:
            e->packInto(p);
            break;
        }
    }
    /* Pack in the "special" entries */

    /* Cache-Control */
}