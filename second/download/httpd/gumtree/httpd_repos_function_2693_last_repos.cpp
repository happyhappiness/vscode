static apr_status_t open_stream(h2_proxy_session *session, const char *url,
                                request_rec *r, int standalone,
                                h2_proxy_stream **pstream)
{
    h2_proxy_stream *stream;
    apr_uri_t puri;
    const char *authority, *scheme, *path;
    apr_status_t status;
    proxy_dir_conf *dconf;

    stream = apr_pcalloc(r->pool, sizeof(*stream));

    stream->pool = r->pool;
    stream->url = url;
    stream->r = r;
    stream->standalone = standalone;
    stream->session = session;
    stream->state = H2_STREAM_ST_IDLE;
    
    stream->input = apr_brigade_create(stream->pool, session->c->bucket_alloc);
    stream->output = apr_brigade_create(stream->pool, session->c->bucket_alloc);
    
    stream->req = h2_proxy_req_create(1, stream->pool, 0);

    status = apr_uri_parse(stream->pool, url, &puri);
    if (status != APR_SUCCESS)
        return status;
    
    scheme = (strcmp(puri.scheme, "h2")? "http" : "https");
    
    dconf = ap_get_module_config(r->per_dir_config, &proxy_module);
    if (dconf->preserve_host) {
        authority = r->hostname;
    }
    else {
        authority = puri.hostname;
        if (!ap_strchr_c(authority, ':') && puri.port
            && apr_uri_port_of_scheme(scheme) != puri.port) {
            /* port info missing and port is not default for scheme: append */
            authority = apr_psprintf(stream->pool, "%s:%d", authority, puri.port);
        }
    }
    
    /* we need this for mapping relative uris in headers ("Link") back
     * to local uris */
    stream->real_server_uri = apr_psprintf(stream->pool, "%s://%s", scheme, authority); 
    stream->p_server_uri = apr_psprintf(stream->pool, "%s://%s", puri.scheme, authority); 
    path = apr_uri_unparse(stream->pool, &puri, APR_URI_UNP_OMITSITEPART);
    h2_proxy_req_make(stream->req, stream->pool, r->method, scheme,
                authority, path, r->headers_in);

    if (dconf->add_forwarded_headers) {
        if (PROXYREQ_REVERSE == r->proxyreq) {
            const char *buf;

            /* Add X-Forwarded-For: so that the upstream has a chance to
             * determine, where the original request came from.
             */
            apr_table_mergen(stream->req->headers, "X-Forwarded-For",
                             r->useragent_ip);

            /* Add X-Forwarded-Host: so that upstream knows what the
             * original request hostname was.
             */
            if ((buf = apr_table_get(r->headers_in, "Host"))) {
                apr_table_mergen(stream->req->headers, "X-Forwarded-Host", buf);
            }

            /* Add X-Forwarded-Server: so that upstream knows what the
             * name of this proxy server is (if there are more than one)
             * XXX: This duplicates Via: - do we strictly need it?
             */
            apr_table_mergen(stream->req->headers, "X-Forwarded-Server",
                             r->server->server_hostname);
        }
    }
    
    /* Tuck away all already existing cookies */
    stream->saves = apr_table_make(r->pool, 2);
    apr_table_do(add_header, stream->saves, r->headers_out, "Set-Cookie", NULL);

    *pstream = stream;
    
    return APR_SUCCESS;
}