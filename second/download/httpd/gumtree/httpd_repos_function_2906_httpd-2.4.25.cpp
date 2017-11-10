static meta *metafix(request_rec *r, const char *buf)
{
    meta *ret = NULL;
    size_t offs = 0;
    const char *p;
    const char *q;
    char *header;
    char *content;
    ap_regmatch_t pmatch[2];
    char delim;

    while (!ap_regexec(seek_meta, buf+offs, 2, pmatch, 0)) {
        header = NULL;
        content = NULL;
        p = buf+offs+pmatch[1].rm_eo;
        while (!apr_isalpha(*++p));
        for (q = p; apr_isalnum(*q) || (*q == '-'); ++q);
        header = apr_pstrndup(r->pool, p, q-p);
        if (strncasecmp(header, "Content-", 8)) {
            /* find content=... string */
            p = apr_strmatch(seek_content, buf+offs+pmatch[0].rm_so,
                              pmatch[0].rm_eo - pmatch[0].rm_so);
            /* if it doesn't contain "content", ignore, don't crash! */
            if (p != NULL) {
                while (*p) {
                    p += 7;
                    while (apr_isspace(*p))
                        ++p;
                    /* XXX Should we search for another content= pattern? */
                    if (*p != '=')
                        break;
                    while (*p && apr_isspace(*++p));
                    if ((*p == '\'') || (*p == '"')) {
                        delim = *p++;
                        for (q = p; *q && *q != delim; ++q);
                        /* No terminating delimiter found? Skip the boggus directive */
                        if (*q != delim)
                           break;
                    } else {
                        for (q = p; *q && !apr_isspace(*q) && (*q != '>'); ++q);
                    }
                    content = apr_pstrndup(r->pool, p, q-p);
                    break;
                }
            }
        }
        else if (!strncasecmp(header, "Content-Type", 12)) {
            ret = apr_palloc(r->pool, sizeof(meta));
            ret->start = offs+pmatch[0].rm_so;
            ret->end = offs+pmatch[0].rm_eo;
        }
        if (header && content) {
#ifndef GO_FASTER
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                          "Adding header [%s: %s] from HTML META",
                          header, content); 
#endif
            apr_table_setn(r->headers_out, header, content);
        }
        offs += pmatch[0].rm_eo;
    }
    return ret;
}