const char *
mimeGetContentType(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);

    if (m == NULL)
        return NULL;

    if (!strcmp(m->content_type, dash_str))
        return NULL;

    return m->content_type;
}