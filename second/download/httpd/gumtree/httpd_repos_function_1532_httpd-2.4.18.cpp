static void vhost_alias_interpolate(request_rec *r, const char *name,
                                    const char *map, const char *uri)
{
    /* 0..9 9..0 */
    enum { MAXDOTS = 19 };
    const char *dots[MAXDOTS+1];
    int ndots;

    char buf[HUGE_STRING_LEN];
    char *dest;
    const char *docroot;

    int N, M, Np, Mp, Nd, Md;
    const char *start, *end;

    const char *p;

    ndots = 0;
    dots[ndots++] = name-1; /* slightly naughty */
    for (p = name; *p; ++p) {
        if (*p == '.' && ndots < MAXDOTS) {
            dots[ndots++] = p;
        }
    }
    dots[ndots] = p;

    r->filename = NULL;

    dest = buf;
    while (*map) {
        if (*map != '%') {
            /* normal characters */
            vhost_alias_checkspace(r, buf, &dest, 1);
            *dest++ = *map++;
            continue;
        }
        /* we are in a format specifier */
        ++map;
        /* %% -> % */
        if (*map == '%') {
            ++map;
            vhost_alias_checkspace(r, buf, &dest, 1);
            *dest++ = '%';
            continue;
        }
        /* port number */
        if (*map == 'p') {
            ++map;
            /* no. of decimal digits in a short plus one */
            vhost_alias_checkspace(r, buf, &dest, 7);
            dest += apr_snprintf(dest, 7, "%d", ap_get_server_port(r));
            continue;
        }
        /* deal with %-N+.-M+ -- syntax is already checked */
        M = 0;   /* value */
        Np = Mp = 0; /* is there a plus? */
        Nd = Md = 0; /* is there a dash? */
        if (*map == '-') ++map, Nd = 1;
        N = *map++ - '0';
        if (*map == '+') ++map, Np = 1;
        if (*map == '.') {
            ++map;
            if (*map == '-') {
                ++map, Md = 1;
            }
            M = *map++ - '0';
            if (*map == '+') {
                ++map, Mp = 1;
            }
        }
        /* note that N and M are one-based indices, not zero-based */
        start = dots[0]+1; /* ptr to the first character */
        end = dots[ndots]; /* ptr to the character after the last one */
        if (N != 0) {
            if (N > ndots) {
                start = "_";
                end = start+1;
            }
            else if (!Nd) {
                start = dots[N-1]+1;
                if (!Np) {
                    end = dots[N];
                }
            }
            else {
                if (!Np) {
                    start = dots[ndots-N]+1;
                }
                end = dots[ndots-N+1];
            }
        }
        if (M != 0) {
            if (M > end - start) {
                start = "_";
                end = start+1;
            }
            else if (!Md) {
                start = start+M-1;
                if (!Mp) {
                    end = start+1;
                }
            }
            else {
                if (!Mp) {
                    start = end-M;
                }
                end = end-M+1;
            }
        }
        vhost_alias_checkspace(r, buf, &dest, end - start);
        for (p = start; p < end; ++p) {
            *dest++ = apr_tolower(*p);
        }
    }
    /* no double slashes */
    if (dest - buf > 0 && dest[-1] == '/') {
        --dest;
    }
    *dest = '\0';

    if (r->filename)
        docroot = apr_pstrcat(r->pool, r->filename, buf, NULL);
    else
        docroot = apr_pstrdup(r->pool, buf);
    r->filename = apr_pstrcat(r->pool, docroot, uri, NULL);
    ap_set_context_info(r, NULL, docroot);
    ap_set_document_root(r, docroot);
}