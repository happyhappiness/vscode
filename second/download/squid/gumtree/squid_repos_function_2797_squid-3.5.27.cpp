HttpHeaderEntry *
HttpHeader::getEntry(HttpHeaderPos * pos) const
{
    assert(pos);
    assert(*pos >= HttpHeaderInitPos && *pos < static_cast<ssize_t>(entries.size()));

    for (++(*pos); *pos < static_cast<ssize_t>(entries.size()); ++(*pos)) {
        if (entries[*pos])
            return static_cast<HttpHeaderEntry*>(entries[*pos]);
    }

    return NULL;
}