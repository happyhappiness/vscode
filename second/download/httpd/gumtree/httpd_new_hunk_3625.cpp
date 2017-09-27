    r->filename = apr_pstrcat(r->pool, "proxy:fcgi://", host, sport, "/",
                              path, NULL);

    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01060)
                  "set r->filename to %s", r->filename);

    rconf = ap_get_module_config(r->request_config, &proxy_fcgi_module);
    if (rconf == NULL) { 
        rconf = apr_pcalloc(r->pool, sizeof(fcgi_req_config_t));
        ap_set_module_config(r->request_config, &proxy_fcgi_module, rconf);
    }

    if (NULL != (pathinfo_type = apr_table_get(r->subprocess_env, "proxy-fcgi-pathinfo"))) {
        /* It has to be on disk for this to work */
        if (!strcasecmp(pathinfo_type, "full")) { 
            rconf->need_dirwalk = 1;
            ap_unescape_url_keep2f(path, 0);
        }
        else if (!strcasecmp(pathinfo_type, "first-dot")) { 
            char *split = ap_strchr(path, '.');
            if (split) { 
                char *slash = ap_strchr(split, '/');
                if (slash) { 
                    r->path_info = apr_pstrdup(r->pool, slash);
                    ap_unescape_url_keep2f(r->path_info, 0);
                    *slash = '\0'; /* truncate path */
                }
            }
        }
        else if (!strcasecmp(pathinfo_type, "last-dot")) { 
            char *split = ap_strrchr(path, '.');
            if (split) { 
                char *slash = ap_strchr(split, '/');
                if (slash) { 
                    r->path_info = apr_pstrdup(r->pool, slash);
                    ap_unescape_url_keep2f(r->path_info, 0);
                    *slash = '\0'; /* truncate path */
                }
            }
        }
        else { 
            /* before proxy-fcgi-pathinfo had multi-values. This requires the
             * the FCGI server to fixup PATH_INFO because it's the entire path
             */
            r->path_info = apr_pstrcat(r->pool, "/", path, NULL);
            if (!strcasecmp(pathinfo_type, "unescape")) { 
                ap_unescape_url_keep2f(r->path_info, 0);
            }
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01061)
                    "set r->path_info to %s", r->path_info);
        }
    }

    return OK;
}

/* Wrapper for apr_socket_sendv that handles updating the worker stats. */
