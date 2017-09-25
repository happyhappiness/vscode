                 * to have nothing to do with the incoming packet
                 */
                r->headers_out = apr_table_make(r->pool,1);
                r->status = HTTP_BAD_GATEWAY;
                r->status_line = "bad gateway";
                return r->status;

            } else {
                /* strip connection listed hop-by-hop headers from response */
                const char *buf;
                p_conn->close += ap_proxy_liststr(apr_table_get(r->headers_out,
                                                                "Connection"),
                                                  "close");
                ap_proxy_clear_connection(p, r->headers_out);
                if ((buf = apr_table_get(r->headers_out, "Content-Type"))) {
                    ap_set_content_type(r, apr_pstrdup(p, buf));
                }            
                ap_proxy_pre_http_request(origin,rp);
            }

            /* handle Via header in response */
            if (conf->viaopt != via_off && conf->viaopt != via_block) {
                /* create a "Via:" response header entry and merge it */
                apr_table_mergen(r->headers_out, "Via",
                                 (conf->viaopt == via_full)
