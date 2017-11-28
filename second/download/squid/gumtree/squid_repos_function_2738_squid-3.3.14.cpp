HttpHeaderEntry *
HttpHeader::getEntry(HttpHeaderPos * pos) const
{
    assert(pos);
    assert(*pos >= HttpHeaderInitPos && *pos < (ssize_t)entries.count);

    for (++(*pos); *pos < (ssize_t)entries.count; ++(*pos)) {
        if (entries.items[*pos])
            return (HttpHeaderEntry*)entries.items[*pos];
    }

    return NULL;
}