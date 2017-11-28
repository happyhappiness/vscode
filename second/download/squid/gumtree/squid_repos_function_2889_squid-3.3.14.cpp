char *
mime_get_header_field(const char *mime, const char *name, const char *prefix)
{
    LOCAL_ARRAY(char, header, GET_HDR_SZ);
    const char *p = NULL;
    char *q = NULL;
    char got = 0;
    const int namelen = name ? strlen(name) : 0;
    const int preflen = prefix ? strlen(prefix) : 0;
    int l;

    if (NULL == mime)
        return NULL;

    assert(NULL != name);

    debugs(25, 5, "mime_get_header: looking for '" << name << "'");

    for (p = mime; *p; p += strcspn(p, "\n\r")) {
        if (strcmp(p, "\r\n\r\n") == 0 || strcmp(p, "\n\n") == 0)
            return NULL;

        while (xisspace(*p))
            ++p;

        if (strncasecmp(p, name, namelen))
            continue;

        if (!xisspace(p[namelen]) && p[namelen] != ':')
            continue;

        l = strcspn(p, "\n\r") + 1;

        if (l > GET_HDR_SZ)
            l = GET_HDR_SZ;

        xstrncpy(header, p, l);

        debugs(25, 5, "mime_get_header: checking '" << header << "'");

        q = header;

        q += namelen;

        if (*q == ':') {
            ++q;
            got = 1;
        }

        while (xisspace(*q)) {
            ++q;
            got = 1;
        }

        if (got && prefix) {
            /* we could process list entries here if we had strcasestr(). */
            /* make sure we did not match a part of another field-value */
            got = !strncasecmp(q, prefix, preflen) && !xisalpha(q[preflen]);
        }

        if (got) {
            debugs(25, 5, "mime_get_header: returning '" << q << "'");
            return q;
        }
    }

    return NULL;
}