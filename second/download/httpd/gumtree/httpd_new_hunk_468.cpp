                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
                r->status = HTTP_BAD_GATEWAY;
                r->status_line = "bad gateway";
                return r->status;
            }

            /* can't have both Content-Length and Transfer-Encoding */
            if (apr_table_get(r->headers_out, "Transfer-Encoding")
                && apr_table_get(r->headers_out, "Content-Length")) {
                /* 2616 section 4.4, point 3: "if both Transfer-Encoding
                 * and Content-Length are received, the latter MUST be
                 * ignored"; so unset it here to prevent any confusion
                 * later. */
                apr_table_unset(r->headers_out, "Content-Length");
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                             r->server,
                             "proxy: server %s returned Transfer-Encoding and Content-Length",
                             p_conn->name);
                p_conn->close += 1;
            }
            
            /* strip connection listed hop-by-hop headers from response */
            p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_out,
                                                            "Connection"),
                                              "close");
            ap_proxy_clear_connection(p, r->headers_out);
            if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                ap_set_content_type(r, apr_pstrdup(p, buf));
            }            
            ap_proxy_pre_http_request(origin,rp);

            /* handle Via header in response */
            if (conf->viaopt != via_off && conf->viaopt != via_block) {
                /* create a "Via:" response header entry and merge it */
                apr_table_mergen(r->headers_out, "Via",
                                 (conf->viaopt == via_full)
