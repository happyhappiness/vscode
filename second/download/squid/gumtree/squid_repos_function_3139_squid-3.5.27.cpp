char const *
mimeGetIcon(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);

    if (m == NULL)
        return NULL;

    if (!strcmp(m->theIcon.getName(), dash_str))
        return NULL;

    return m->theIcon.getName();
}