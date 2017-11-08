static const char *log_request_line(request_rec *r, char *a)
{
    /* NOTE: If the original request contained a password, we
     * re-write the request line here to contain XXXXXX instead:
     * (note the truncation before the protocol string for HTTP/0.9 requests)
     * (note also that r->the_request contains the unmodified request)
     */
    return ap_escape_logitem(r->pool,
                             (r->parsed_uri.password)
                               ? apr_pstrcat(r->pool, r->method, " ",
                                             apr_uri_unparse(r->pool,
                                                             &r->parsed_uri, 0),
                                             r->assbackwards ? NULL : " ",
                                             r->protocol, NULL)
                               : r->the_request);
}