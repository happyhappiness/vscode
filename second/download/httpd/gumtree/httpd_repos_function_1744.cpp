static int proxy_needsdomain(request_rec *r, const char *url, const char *domain)
{
    char *nuri;
    const char *ref;

    /* We only want to worry about GETs */
    if (!r->proxyreq || r->method_number != M_GET || !r->parsed_uri.hostname)
        return DECLINED;

    /* If host does contain a dot already, or it is "localhost", decline */
    if (strchr(r->parsed_uri.hostname, '.') != NULL /* has domain, or IPv4 literal */
     || strchr(r->parsed_uri.hostname, ':') != NULL /* IPv6 literal */
     || strcasecmp(r->parsed_uri.hostname, "localhost") == 0)
        return DECLINED;    /* host name has a dot already */

    ref = apr_table_get(r->headers_in, "Referer");

    /* Reassemble the request, but insert the domain after the host name */
    /* Note that the domain name always starts with a dot */
    r->parsed_uri.hostname = apr_pstrcat(r->pool, r->parsed_uri.hostname,
                                         domain, NULL);
    nuri = apr_uri_unparse(r->pool,
                           &r->parsed_uri,
                           APR_URI_UNP_REVEALPASSWORD);

    apr_table_set(r->headers_out, "Location", nuri);
    ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r,
                  "Domain missing: %s sent to %s%s%s", r->uri,
                  apr_uri_unparse(r->pool, &r->parsed_uri,
                                  APR_URI_UNP_OMITUSERINFO),
                  ref ? " from " : "", ref ? ref : "");

    return HTTP_MOVED_PERMANENTLY;
}