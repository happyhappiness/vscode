static void fix_uds_filename(request_rec *r, char **url) 
{
    char *ptr, *ptr2;
    if (!r || !r->filename) return;

    if (!strncmp(r->filename, "proxy:", 6) &&
            (ptr2 = ap_strcasestr(r->filename, "unix:")) &&
            (ptr = ap_strchr(ptr2, '|'))) {
        apr_uri_t urisock;
        apr_status_t rv;
        *ptr = '\0';
        rv = apr_uri_parse(r->pool, ptr2, &urisock);
        if (rv == APR_SUCCESS) {
            char *rurl = ptr+1;
            char *sockpath = ap_runtime_dir_relative(r->pool, urisock.path);
            apr_table_setn(r->notes, "uds_path", sockpath);
            *url = apr_pstrdup(r->pool, rurl); /* so we get the scheme for the uds */
            /* r->filename starts w/ "proxy:", so add after that */
            memmove(r->filename+6, rurl, strlen(rurl)+1);
            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                    "*: rewrite of url due to UDS(%s): %s (%s)",
                    sockpath, *url, r->filename);
        }
        else {
            *ptr = '|';
        }
    }
}