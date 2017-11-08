static int proxy_fcgi_canon(request_rec *r, char *url)
{
    char *host, sport[7];
    const char *err;
    char *path;
    apr_port_t port, def_port;
    fcgi_req_config_t *rconf = NULL;
    const char *pathinfo_type = NULL;

    if (strncasecmp(url, "fcgi:", 5) == 0) {
        url += 5;
    }
    else {
        return DECLINED;
    }

    port = def_port = ap_proxy_port_of_scheme("fcgi");

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                 "canonicalising URL %s", url);
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01059)
                      "error parsing URL %s: %s", url, err);
        return HTTP_BAD_REQUEST;
    }

    if (port != def_port)
        apr_snprintf(sport, sizeof(sport), ":%d", port);
    else
        sport[0] = '\0';

    if (ap_strchr_c(host, ':')) {
        /* if literal IPv6 address */
        host = apr_pstrcat(r->pool, "[", host, "]", NULL);
    }

    if (apr_table_get(r->notes, "proxy-nocanon")) {
        path = url;   /* this is the raw path */
    }
    else {
        path = ap_proxy_canonenc(r->pool, url, strlen(url), enc_path, 0,
                             r->proxyreq);
    }
    if (path == NULL)
        return HTTP_BAD_REQUEST;

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