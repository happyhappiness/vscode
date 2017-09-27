                 */
                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                char *ptr;
                char *ptr2;
                ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                              "*: found reverse proxy worker for %s", *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
                /*
                 * The reverse worker does not keep connections alive, so
                 * ensure that mod_proxy_http does the correct thing
                 * regarding the Connection header in the request.
                 */
                apr_table_setn(r->subprocess_env, "proxy-nokeepalive", "1");
                /*
                 * In the case of the generic reverse proxy, we need to see if we
                 * were passed a UDS url (eg: from mod_proxy) and adjust uds_path
                 * as required.
                 *
                 * NOTE: Here we use a quick note lookup, but we could also
                 * check to see if r->filename starts with 'proxy:'
                 */
                if (apr_table_get(r->notes, "rewrite-proxy") &&
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
        }
    }
    else if (access_status == DECLINED && *balancer != NULL) {
        /* All the workers are busy */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00934)
