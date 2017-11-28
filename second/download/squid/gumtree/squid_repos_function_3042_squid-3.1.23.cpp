char *
mimeGetContentEncoding(const char *fn)
{
    mimeEntry *m = mimeGetEntry(fn, 0);

    if (m == NULL)
        return NULL;

    if (!strcmp(m->content_encoding, dash_str))
        return NULL;

    return m->content_encoding;
}