static char *lcase_header_name_return_body(char *header, request_rec *r)
{
    char *cp = header;

    for ( ; *cp && *cp != ':' ; ++cp) {
        *cp = apr_tolower(*cp);
    }

    if (!*cp) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00681)
                      "Syntax error in type map, no ':' in %s for header %s",
                      r->filename, header);
        return NULL;
    }

    do {
        ++cp;
    } while (apr_isspace(*cp));

    if (!*cp) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00682)
                      "Syntax error in type map --- no header body: %s for %s",
                      r->filename, header);
        return NULL;
    }

    return cp;
}