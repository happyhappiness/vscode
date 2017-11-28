static mimeEntry *
mimeGetEntry(const char *fn, int skip_encodings)
{
    mimeEntry *m;
    char *t;
    char *name = xstrdup(fn);

    do {
        t = NULL;

        for (m = MimeTable; m; m = m->next) {
            if (regexec(&m->compiled_pattern, name, 0, 0, 0) == 0)
                break;
        }

        if (!skip_encodings)
            (void) 0;
        else if (m == NULL)
            (void) 0;
        else if (strcmp(m->content_type, dash_str))
            (void) 0;
        else if (!strcmp(m->content_encoding, dash_str))
            (void) 0;
        else {
            /* Assume we matched /\.\w$/ and cut off the last extension */
            if ((t = strrchr(name, '.'))) {
                *t = '\0';
            } else {
                /* What? A encoding without a extension? */
                m = NULL;
            }
        }
    } while (t);

    xfree(name);
    return m;
}