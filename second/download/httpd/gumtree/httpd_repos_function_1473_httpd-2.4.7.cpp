static int imap_reply(request_rec *r, const char *redirect)
{
    if (!strcasecmp(redirect, "error")) {
        /* they actually requested an error! */
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    if (!strcasecmp(redirect, "nocontent")) {
        /* tell the client to keep the page it has */
        return HTTP_NO_CONTENT;
    }
    if (redirect && *redirect) {
        /* must be a URL, so redirect to it */
        apr_table_setn(r->headers_out, "Location", redirect);
        return HTTP_MOVED_TEMPORARILY;
    }
    return HTTP_INTERNAL_SERVER_ERROR;
}