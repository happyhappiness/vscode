static void vhost_alias_interpolate(request_rec *r, const char *name,
                                    const char *map, const char *uri)
{
    /* 0..9 9..0 */
    enum { MAXDOTS = 19 };
    const char *dots[MAXDOTS+1];
    int ndots;

    char buf[HUGE_STRING_LEN];
    char *dest, last;

    int N, M, Np, Mp, Nd, Md;
    const char *start, *end;

    const char *p;

    ndots = 0;
    dots[ndots++] = name-1; /* slightly naughty */
    for (p = name; *p; ++p){
        if (*p == '.' && ndots < MAXDOTS) {
            dots[ndots++] = p;
        }
    }
    dots[ndots] = p;

    r->filename = NULL;

    dest = buf;
    last = '\0';
    while (*map) {
        if (*map != '%') {
            /* normal characters */
            vhost_alias_checkspace(r, buf, &dest, 1);
            last = *dest++ = *map++;
            continue;
        }
        /* we are in a format specifier */
        ++map;
        /* can't be a slash */
        last = '\0';
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
        N = M = 0;   /* value */
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
    *dest = '\0';
    /* no double slashes */
    if (last == '/') {
        ++uri;
    }

    if (r->filename) {
        r->filename = apr_pstrcat(r->pool, r->filename, buf, uri, NULL);
    }
    else {
        r->filename = apr_pstrcat(r->pool, buf, uri, NULL);
    }
}