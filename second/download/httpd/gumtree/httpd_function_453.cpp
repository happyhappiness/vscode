static
apr_status_t ap_proxy_http_request(apr_pool_t *p, request_rec *r,
                                   proxy_http_conn_t *p_conn, conn_rec *origin, 
                                   proxy_server_conf *conf,
                                   apr_uri_t *uri,
                                   char *url, apr_bucket_brigade *bb,
                                   char *server_portstr) {
    conn_rec *c = r->connection;
    char *buf;
    apr_bucket *e;
    const apr_array_header_t *headers_in_array;
    const apr_table_entry_t *headers_in;
    int counter, seen_eos;
    apr_status_t status;

    /*
     * Send the HTTP/1.1 request to the remote server
     */

    /* strip connection listed hop-by-hop headers from the request */
    /* even though in theory a connection: close coming from the client
     * should not affect the connection to the server, it's unlikely
     * that subsequent client requests will hit this thread/process, so
     * we cancel server keepalive if the client does.
     */
    p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_in,
                                                     "Connection"), "close");
    /* sub-requests never use keepalives */
    if (r->main) {
        p_conn->close++;
    }

    ap_proxy_clear_connection(p, r->headers_in);
    if (p_conn->close) {
        apr_table_setn(r->headers_in, "Connection", "close");
        origin->keepalive = AP_CONN_CLOSE;
    }

    if ( apr_table_get(r->subprocess_env,"force-proxy-request-1.0")) {
        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.0" CRLF, NULL);
    } else {
        buf = apr_pstrcat(p, r->method, " ", url, " HTTP/1.1" CRLF, NULL);
    }
    if ( apr_table_get(r->subprocess_env,"proxy-nokeepalive")) {
        apr_table_unset(r->headers_in, "Connection");
        origin->keepalive = AP_CONN_CLOSE;
    }
    ap_xlate_proto_to_ascii(buf, strlen(buf));
    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    if ( conf->preserve_host == 0 ) {
        if (uri->port_str && uri->port != DEFAULT_HTTP_PORT) {
            buf = apr_pstrcat(p, "Host: ", uri->hostname, ":", uri->port_str, CRLF,
                            NULL);
        } else {
            buf = apr_pstrcat(p, "Host: ", uri->hostname, CRLF, NULL);
        }
    } 
    else {
        /* don't want to use r->hostname, as the incoming header might have a 
         * port attached 
         */
        const char* hostname = apr_table_get(r->headers_in,"Host");        
        if (!hostname) {
            hostname =  r->server->server_hostname;
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "proxy: no HTTP 0.9 request (with no host line) "
                          "on incoming request and preserve host set "
                          "forcing hostname to be %s for uri %s", 
                          hostname, 
                          r->uri );
        }
        buf = apr_pstrcat(p, "Host: ", hostname, CRLF, NULL);
    }
    ap_xlate_proto_to_ascii(buf, strlen(buf));
    e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);        
    APR_BRIGADE_INSERT_TAIL(bb, e);

    /* handle Via */
    if (conf->viaopt == via_block) {
        /* Block all outgoing Via: headers */
        apr_table_unset(r->headers_in, "Via");
    } else if (conf->viaopt != via_off) {
        /* Create a "Via:" request header entry and merge it */
        /* Generate outgoing Via: header with/without server comment: */
        apr_table_mergen(r->headers_in, "Via",
                         (conf->viaopt == via_full)
                         ? apr_psprintf(p, "%d.%d %s%s (%s)",
                                        HTTP_VERSION_MAJOR(r->proto_num),
                                        HTTP_VERSION_MINOR(r->proto_num),
                                        ap_get_server_name(r), server_portstr,
                                        AP_SERVER_BASEVERSION)
                         : apr_psprintf(p, "%d.%d %s%s",
                                        HTTP_VERSION_MAJOR(r->proto_num),
                                        HTTP_VERSION_MINOR(r->proto_num),
                                        ap_get_server_name(r), server_portstr)
        );
    }

    /* X-Forwarded-*: handling
     *
     * XXX Privacy Note:
     * -----------------
     *
     * These request headers are only really useful when the mod_proxy
     * is used in a reverse proxy configuration, so that useful info
     * about the client can be passed through the reverse proxy and on
     * to the backend server, which may require the information to
     * function properly.
     *
     * In a forward proxy situation, these options are a potential
     * privacy violation, as information about clients behind the proxy
     * are revealed to arbitrary servers out there on the internet.
     *
     * The HTTP/1.1 Via: header is designed for passing client
     * information through proxies to a server, and should be used in
     * a forward proxy configuation instead of X-Forwarded-*. See the
     * ProxyVia option for details.
     */

    if (PROXYREQ_REVERSE == r->proxyreq) {
        const char *buf;

        /* Add X-Forwarded-For: so that the upstream has a chance to
         * determine, where the original request came from.
         */
        apr_table_mergen(r->headers_in, "X-Forwarded-For",
                       r->connection->remote_ip);

        /* Add X-Forwarded-Host: so that upstream knows what the
         * original request hostname was.
         */
        if ((buf = apr_table_get(r->headers_in, "Host"))) {
            apr_table_mergen(r->headers_in, "X-Forwarded-Host", buf);
        }

        /* Add X-Forwarded-Server: so that upstream knows what the
         * name of this proxy server is (if there are more than one)
         * XXX: This duplicates Via: - do we strictly need it?
         */
        apr_table_mergen(r->headers_in, "X-Forwarded-Server",
                       r->server->server_hostname);
    }

    /* send request headers */
    proxy_run_fixups(r);
    headers_in_array = apr_table_elts(r->headers_in);
    headers_in = (const apr_table_entry_t *) headers_in_array->elts;
    for (counter = 0; counter < headers_in_array->nelts; counter++) {
        if (headers_in[counter].key == NULL || headers_in[counter].val == NULL

        /* Clear out hop-by-hop request headers not to send
         * RFC2616 13.5.1 says we should strip these headers
         */
                /* Already sent */
            || !apr_strnatcasecmp(headers_in[counter].key, "Host")

            || !apr_strnatcasecmp(headers_in[counter].key, "Keep-Alive")
            || !apr_strnatcasecmp(headers_in[counter].key, "TE")
            || !apr_strnatcasecmp(headers_in[counter].key, "Trailer")
            || !apr_strnatcasecmp(headers_in[counter].key, "Transfer-Encoding")
            || !apr_strnatcasecmp(headers_in[counter].key, "Upgrade")

        /* XXX: @@@ FIXME: "Proxy-Authorization" should *only* be 
         * suppressed if THIS server requested the authentication,
         * not when a frontend proxy requested it!
         *
         * The solution to this problem is probably to strip out
         * the Proxy-Authorisation header in the authorisation
         * code itself, not here. This saves us having to signal
         * somehow whether this request was authenticated or not.
         */
            || !apr_strnatcasecmp(headers_in[counter].key,"Proxy-Authorization")
            || !apr_strnatcasecmp(headers_in[counter].key,"Proxy-Authenticate")) {
            continue;
        }
        /* for sub-requests, ignore freshness/expiry headers */
        if (r->main) {
                if (headers_in[counter].key == NULL || headers_in[counter].val == NULL
                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Match")
                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Modified-Since")
                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Range")
                     || !apr_strnatcasecmp(headers_in[counter].key, "If-Unmodified-Since")                     
                     || !apr_strnatcasecmp(headers_in[counter].key, "If-None-Match")) {
                    continue;
                }

                /* If you POST to a page that gets server-side parsed
                 * by mod_include, and the parsing results in a reverse
                 * proxy call, the proxied request will be a GET, but
                 * its request_rec will have inherited the Content-Length
                 * of the original request (the POST for the enclosing
                 * page).  We can't send the original POST's request body
                 * as part of the proxied subrequest, so we need to avoid
                 * sending the corresponding content length.  Otherwise,
                 * the server to which we're proxying will sit there
                 * forever, waiting for a request body that will never
                 * arrive.
                 */
                if ((r->method_number == M_GET) && headers_in[counter].key &&
                    !apr_strnatcasecmp(headers_in[counter].key,
                                       "Content-Length")) {
                    continue;
                }
        }


        buf = apr_pstrcat(p, headers_in[counter].key, ": ",
                          headers_in[counter].val, CRLF,
                          NULL);
        ap_xlate_proto_to_ascii(buf, strlen(buf));
        e = apr_bucket_pool_create(buf, strlen(buf), p, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }

    /* add empty line at the end of the headers */
#if APR_CHARSET_EBCDIC
    e = apr_bucket_immortal_create("\015\012", 2, c->bucket_alloc);
#else
    e = apr_bucket_immortal_create(CRLF, sizeof(CRLF)-1, c->bucket_alloc);
#endif
    APR_BRIGADE_INSERT_TAIL(bb, e);
    e = apr_bucket_flush_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);

    status = ap_pass_brigade(origin->output_filters, bb);

    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: request failed to %pI (%s)",
                     p_conn->addr, p_conn->name);
        return status;
    }

    /* send the request data, if any. */
    seen_eos = 0;
    do {
        status = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                                APR_BLOCK_READ, HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return status;
        }

        /* If this brigade contain EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
            /* As a shortcut, if this brigade is simply an EOS bucket,
             * don't send anything down the filter chain.
             */
            if (APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(bb))) {
                break;
            }

            /* We can't pass this EOS to the output_filters. */
            e = APR_BRIGADE_LAST(bb);
            apr_bucket_delete(e);
            seen_eos = 1;
        }

        e = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);

        status = ap_pass_brigade(origin->output_filters, bb);
        if (status != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                         "proxy: pass request data failed to %pI (%s)",
                         p_conn->addr, p_conn->name);
            return status;
        }
        apr_brigade_cleanup(bb);
    } while (!seen_eos);

    return APR_SUCCESS;
}