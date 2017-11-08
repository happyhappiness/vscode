static int dav_created(request_rec *r, const char *locn, const char *what,
                       int replaced)
{
    const char *body;

    if (locn == NULL) {
        locn = r->uri;
    }

    /* did the target resource already exist? */
    if (replaced) {
        /* Apache will supply a default message */
        return HTTP_NO_CONTENT;
    }

    /* Per HTTP/1.1, S10.2.2: add a Location header to contain the
     * URI that was created. */

    /* Convert locn to an absolute URI, and return in Location header */
    apr_table_setn(r->headers_out, "Location", ap_construct_url(r->pool, locn, r));

    /* ### insert an ETag header? see HTTP/1.1 S10.2.2 */

    /* Apache doesn't allow us to set a variable body for HTTP_CREATED, so
     * we must manufacture the entire response. */
    body = apr_psprintf(r->pool, "%s %s has been created.",
                        what, ap_escape_html(r->pool, locn));
    return dav_error_response(r, HTTP_CREATED, body);
}