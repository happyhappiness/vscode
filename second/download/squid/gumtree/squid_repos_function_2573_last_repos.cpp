const SBuf
mimeGetIcon(const char *fn)
{
    MimeEntry *m = mimeGetEntry(fn, 1);

    if (!m || !m->theIcon.getName().cmp(dash_str))
        return SBuf();

    return m->theIcon.getName();
}