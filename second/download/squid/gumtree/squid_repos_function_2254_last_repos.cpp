void
HttpHeader::packInto(Packable * p, bool mask_sensitive_info) const
{
    HttpHeaderPos pos = HttpHeaderInitPos;
    const HttpHeaderEntry *e;
    assert(p);
    debugs(55, 7, this << " into " << p <<
           (mask_sensitive_info ? " while masking" : ""));
    /* pack all entries one by one */
    while ((e = getEntry(&pos))) {
        if (!mask_sensitive_info) {
            e->packInto(p);
            continue;
        }

        bool maskThisEntry = false;
        switch (e->id) {
        case Http::HdrType::AUTHORIZATION:
        case Http::HdrType::PROXY_AUTHORIZATION:
            maskThisEntry = true;
            break;

        case Http::HdrType::FTP_ARGUMENTS:
            if (const HttpHeaderEntry *cmd = findEntry(Http::HdrType::FTP_COMMAND))
                maskThisEntry = (cmd->value == "PASS");
            break;

        default:
            break;
        }
        if (maskThisEntry) {
            p->append(e->name.rawBuf(), e->name.size());
            p->append(": ** NOT DISPLAYED **\r\n", 23);
        } else {
            e->packInto(p);
        }

    }
    /* Pack in the "special" entries */

    /* Cache-Control */
}