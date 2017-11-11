char *ssl_var_lookup(apr_pool_t *p, server_rec *s, conn_rec *c, request_rec *r, char *var)
{
    SSLModConfigRec *mc = myModConfig(s);
    const char *result;
    BOOL resdup;
    apr_time_exp_t tm;

    result = NULL;
    resdup = TRUE;

    /*
     * When no pool is given try to find one
     */
    if (p == NULL) {
        if (r != NULL)
            p = r->pool;
        else if (c != NULL)
            p = c->pool;
        else
            p = mc->pPool;
    }

    /*
     * Request dependent stuff
     */
    if (r != NULL) {
        switch (var[0]) {
        case 'H':
        case 'h':
            if (strcEQ(var, "HTTP_USER_AGENT"))
                result = apr_table_get(r->headers_in, "User-Agent");
            else if (strcEQ(var, "HTTP_REFERER"))
                result = apr_table_get(r->headers_in, "Referer");
            else if (strcEQ(var, "HTTP_COOKIE"))
                result = apr_table_get(r->headers_in, "Cookie");
            else if (strcEQ(var, "HTTP_FORWARDED"))
                result = apr_table_get(r->headers_in, "Forwarded");
            else if (strcEQ(var, "HTTP_HOST"))
                result = apr_table_get(r->headers_in, "Host");
            else if (strcEQ(var, "HTTP_PROXY_CONNECTION"))
                result = apr_table_get(r->headers_in, "Proxy-Connection");
            else if (strcEQ(var, "HTTP_ACCEPT"))
                result = apr_table_get(r->headers_in, "Accept");
            else if (strlen(var) > 5 && strcEQn(var, "HTTP:", 5))
                /* all other headers from which we are still not know about */
                result = apr_table_get(r->headers_in, var+5);
            break;

        case 'R':
        case 'r':
            if (strcEQ(var, "REQUEST_METHOD"))
                result = r->method;
            else if (strcEQ(var, "REQUEST_SCHEME"))
                result = ap_http_scheme(r);
            else if (strcEQ(var, "REQUEST_URI"))
                result = r->uri;
            else if (strcEQ(var, "REQUEST_FILENAME"))
                result = r->filename;
            else if (strcEQ(var, "REMOTE_HOST"))
                result = ap_get_remote_host(r->connection, r->per_dir_config,
                                            REMOTE_NAME, NULL);
            else if (strcEQ(var, "REMOTE_IDENT"))
                result = ap_get_remote_logname(r);
            else if (strcEQ(var, "REMOTE_USER"))
                result = r->user;
            break;

        case 'S':
        case 's':
            if (strcEQn(var, "SSL", 3)) break; /* shortcut common case */

            if (strcEQ(var, "SERVER_ADMIN"))
                result = r->server->server_admin;
            else if (strcEQ(var, "SERVER_NAME"))
                result = ap_get_server_name(r);
            else if (strcEQ(var, "SERVER_PORT"))
                result = apr_psprintf(p, "%u", ap_get_server_port(r));
            else if (strcEQ(var, "SERVER_PROTOCOL"))
                result = r->protocol;
            else if (strcEQ(var, "SCRIPT_FILENAME"))
                result = r->filename;
            break;

        default:
            if (strcEQ(var, "PATH_INFO"))
                result = r->path_info;
            else if (strcEQ(var, "QUERY_STRING"))
                result = r->args;
            else if (strcEQ(var, "IS_SUBREQ"))
                result = (r->main != NULL ? "true" : "false");
            else if (strcEQ(var, "DOCUMENT_ROOT"))
                result = ap_document_root(r);
            else if (strcEQ(var, "AUTH_TYPE"))
                result = r->ap_auth_type;
            else if (strcEQ(var, "THE_REQUEST"))
                result = r->the_request;
            break;
        }
    }

    /*
     * Connection stuff
     */
    if (result == NULL && c != NULL) {
        SSLConnRec *sslconn = myConnConfig(c);
        if (strlen(var) > 4 && strcEQn(var, "SSL_", 4)
            && sslconn && sslconn->ssl)
            result = ssl_var_lookup_ssl(p, c, var+4);
        else if (strcEQ(var, "REMOTE_ADDR"))
            result = c->remote_ip;
        else if (strcEQ(var, "HTTPS")) {
            if (sslconn && sslconn->ssl)
                result = "on";
            else
                result = "off";
        }
    }

    /*
     * Totally independent stuff
     */
    if (result == NULL) {
        if (strlen(var) > 12 && strcEQn(var, "SSL_VERSION_", 12))
            result = ssl_var_lookup_ssl_version(p, var+12);
        else if (strcEQ(var, "SERVER_SOFTWARE"))
            result = ap_get_server_version();
        else if (strcEQ(var, "API_VERSION")) {
            result = apr_itoa(p, MODULE_MAGIC_NUMBER);
            resdup = FALSE;
        }
        else if (strcEQ(var, "TIME_YEAR")) {
            apr_time_exp_lt(&tm, apr_time_now());
            result = apr_psprintf(p, "%02d%02d",
                                 (tm.tm_year / 100) + 19, tm.tm_year % 100);
            resdup = FALSE;
        }
#define MKTIMESTR(format, tmfield) \
            apr_time_exp_lt(&tm, apr_time_now()); \
            result = apr_psprintf(p, format, tm.tmfield); \
            resdup = FALSE;
        else if (strcEQ(var, "TIME_MON")) {
            MKTIMESTR("%02d", tm_mon+1)
        }
        else if (strcEQ(var, "TIME_DAY")) {
            MKTIMESTR("%02d", tm_mday)
        }
        else if (strcEQ(var, "TIME_HOUR")) {
            MKTIMESTR("%02d", tm_hour)
        }
        else if (strcEQ(var, "TIME_MIN")) {
            MKTIMESTR("%02d", tm_min)
        }
        else if (strcEQ(var, "TIME_SEC")) {
            MKTIMESTR("%02d", tm_sec)
        }
        else if (strcEQ(var, "TIME_WDAY")) {
            MKTIMESTR("%d", tm_wday)
        }
        else if (strcEQ(var, "TIME")) {
            apr_time_exp_lt(&tm, apr_time_now());
            result = apr_psprintf(p,
                        "%02d%02d%02d%02d%02d%02d%02d", (tm.tm_year / 100) + 19,
                        (tm.tm_year % 100), tm.tm_mon+1, tm.tm_mday,
                        tm.tm_hour, tm.tm_min, tm.tm_sec);
            resdup = FALSE;
        }
        /* all other env-variables from the parent Apache process */
        else if (strlen(var) > 4 && strcEQn(var, "ENV:", 4)) {
            result = apr_table_get(r->notes, var+4);
            if (result == NULL)
                result = apr_table_get(r->subprocess_env, var+4);
            if (result == NULL)
                result = getenv(var+4);
        }
    }

    if (result != NULL && resdup)
        result = apr_pstrdup(p, result);
    if (result == NULL)
        result = "";
    return (char *)result;
}