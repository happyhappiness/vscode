HttpReply *
HttpReply::make304() const
{
    static const Http::HdrType ImsEntries[] = {Http::HdrType::DATE, Http::HdrType::CONTENT_TYPE, Http::HdrType::EXPIRES, Http::HdrType::LAST_MODIFIED, /* eof */ Http::HdrType::OTHER};

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
    rv->sline.set(Http::ProtocolVersion(), Http::scNotModified, NULL);

    for (t = 0; ImsEntries[t] != Http::HdrType::OTHER; ++t) {
        if ((e = header.findEntry(ImsEntries[t])))
            rv->header.addEntry(e->clone());
    }

    rv->putCc(cache_control);

    /* rv->body */
    return rv;
}