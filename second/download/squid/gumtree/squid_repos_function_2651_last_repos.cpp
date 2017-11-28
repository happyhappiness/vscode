void
ErrorState::DenyInfoLocation(const char *name, HttpRequest *, MemBuf &result)
{
    char const *m = name;
    char const *p = m;
    char const *t;

    if (m[0] == '3')
        m += 4; // skip "3xx:"

    while ((p = strchr(m, '%'))) {
        result.append(m, p - m);       /* copy */
        t = Convert(*++p, true, true);       /* convert */
        result.appendf("%s", t);        /* copy */
        m = p + 1;                     /* advance */
    }

    if (*m)
        result.appendf("%s", m);        /* copy tail */

    assert((size_t)result.contentSize() == strlen(result.content()));
}