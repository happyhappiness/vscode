static void h2_proxy_stream_end_headers_out(h2_proxy_stream *stream) 
{
    h2_proxy_session *session = stream->session;
    request_rec *r = stream->r;
    apr_pool_t *p = r->pool;
    
    /* Now, add in the cookies from the response to the ones already saved */
    apr_table_do(add_header, stream->saves, r->headers_out, "Set-Cookie", NULL);
    
    /* and now load 'em all in */
    if (!apr_is_empty_table(stream->saves)) {
        apr_table_unset(r->headers_out, "Set-Cookie");
        r->headers_out = apr_table_overlay(p, r->headers_out, stream->saves);
    }
    
    /* handle Via header in response */
    if (session->conf->viaopt != via_off 
        && session->conf->viaopt != via_block) {
        const char *server_name = ap_get_server_name(stream->r);
        apr_port_t port = ap_get_server_port(stream->r);
        char portstr[32];
        
        /* If USE_CANONICAL_NAME_OFF was configured for the proxy virtual host,
         * then the server name returned by ap_get_server_name() is the
         * origin server name (which doesn't make sense with Via: headers)
         * so we use the proxy vhost's name instead.
         */
        if (server_name == stream->r->hostname) {
            server_name = stream->r->server->server_hostname;
        }
        if (ap_is_default_port(port, stream->r)) {
            portstr[0] = '\0';
        }
        else {
            apr_snprintf(portstr, sizeof(portstr), ":%d", port);
        }

        /* create a "Via:" response header entry and merge it */
        apr_table_addn(r->headers_out, "Via",
                       (session->conf->viaopt == via_full)
                       ? apr_psprintf(p, "%d.%d %s%s (%s)",
                                      HTTP_VERSION_MAJOR(r->proto_num),
                                      HTTP_VERSION_MINOR(r->proto_num),
                                      server_name, portstr,
                                      AP_SERVER_BASEVERSION)
                       : apr_psprintf(p, "%d.%d %s%s",
                                      HTTP_VERSION_MAJOR(r->proto_num),
                                      HTTP_VERSION_MINOR(r->proto_num),
                                      server_name, portstr)
                       );
    }
    
    if (APLOGrtrace2(stream->r)) {
        ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, stream->r, 
                      "h2_proxy_stream(%s-%d), header_out after merging", 
                      stream->session->id, stream->id);
        apr_table_do(log_header, stream, stream->r->headers_out, NULL);
    }
}