void
mimeFreeMemory(void)
{
    mimeEntry *m;

    while ((m = MimeTable)) {
        MimeTable = m->next;
        safe_free(m->pattern);
        safe_free(m->content_type);
        safe_free(m->icon);
        safe_free(m->content_encoding);
        regfree(&m->compiled_pattern);
        delete m;
    }

    MimeTableTail = &MimeTable;
}