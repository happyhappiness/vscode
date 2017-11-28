HttpReply *
HttpReply::make304() const
{
    static const http_hdr_type ImsEntries[] = {HDR_DATE, HDR_CONTENT_TYPE, HDR_EXPIRES, HDR_LAST_MODIFIED, /* eof */ HDR_OTHER};

    HttpReply *rv = new HttpReply;
    int t;
    HttpHeaderEntry *e;

    /* rv->content_length; */
    rv->date = date;
    rv->last_modified = last_modified;
    rv->expires = expires;
    rv->content_type = content_type;
    /* rv->content_range */
    /* rv->keep_alive */
    rv->sline.set(Http::ProtocolVersion(1,1), Http::scNotModified, NULL);

    for (t = 0; ImsEntries[t] != HDR_OTHER; ++t)
        if ((e = header.findEntry(ImsEntries[t])))
            rv->header.addEntry(e->clone());

    rv->putCc(cache_control);

    /* rv->body */
    return rv;
}