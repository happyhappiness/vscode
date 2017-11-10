char *ssl_var_lookup(apr_pool_t *p, server_rec *s, conn_rec *c, request_rec *r, char *var)
{
    SSLConnRec *sslconn;
    SSLModConfigRec *mc = myModConfig(s);
    char *result;
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
        if (strcEQ(var, "HTTP_USER_AGENT"))
            result = ssl_var_lookup_header(p, r, "User-Agent");
        else if (strcEQ(var, "HTTP_REFERER"))
            result = ssl_var_lookup_header(p, r, "Referer");
        else if (strcEQ(var, "HTTP_COOKIE"))
            result = ssl_var_lookup_header(p, r, "Cookie");
        else if (strcEQ(var, "HTTP_FORWARDED"))
            result = ssl_var_lookup_header(p, r, "Forwarded");
        else if (strcEQ(var, "HTTP_HOST"))
            result = ssl_var_lookup_header(p, r, "Host");
        else if (strcEQ(var, "HTTP_PROXY_CONNECTION"))
            result = ssl_var_lookup_header(p, r, "Proxy-Connection");
        else if (strcEQ(var, "HTTP_ACCEPT"))
            result = ssl_var_lookup_header(p, r, "Accept");
        else if (strlen(var) > 5 && strcEQn(var, "HTTP:", 5))
            /* all other headers from which we are still not know about */
            result = ssl_var_lookup_header(p, r, var+5);
        else if (strcEQ(var, "THE_REQUEST"))
            result = r->the_request;
        else if (strcEQ(var, "REQUEST_METHOD"))
            result = (char *)(r->method);
        else if (strcEQ(var, "REQUEST_SCHEME"))
            result = (char *)ap_http_method(r);
        else if (strcEQ(var, "REQUEST_URI"))
            result = r->uri;
        else if (strcEQ(var, "SCRIPT_FILENAME") ||
                 strcEQ(var, "REQUEST_FILENAME"))
            result = r->filename;
        else if (strcEQ(var, "PATH_INFO"))
            result = r->path_info;
        else if (strcEQ(var, "QUERY_STRING"))
            result = r->args;
        else if (strcEQ(var, "REMOTE_HOST"))
            result = (char *)ap_get_remote_host(r->connection,
					r->per_dir_config, REMOTE_NAME, NULL);
        else if (strcEQ(var, "REMOTE_IDENT"))
            result = (char *)ap_get_remote_logname(r);
        else if (strcEQ(var, "IS_SUBREQ"))
            result = (r->main != NULL ? "true" : "false");
        else if (strcEQ(var, "DOCUMENT_ROOT"))
            result = (char *)ap_document_root(r);
        else if (strcEQ(var, "SERVER_ADMIN"))
            result = r->server->server_admin;
        else if (strcEQ(var, "SERVER_NAME"))
            result = (char *)ap_get_server_name(r);
        else if (strcEQ(var, "SERVER_PORT"))
            result = apr_psprintf(p, "%u", ap_get_server_port(r));
        else if (strcEQ(var, "SERVER_PROTOCOL"))
            result = r->protocol;
    }

    /*
     * Connection stuff
     */
    if (result == NULL && c != NULL) {
        sslconn = myConnConfig(c);
        if (strcEQ(var, "REMOTE_ADDR"))
            result = c->remote_ip;
        else if (strcEQ(var, "REMOTE_USER"))
            result = r->user;
        else if (strcEQ(var, "AUTH_TYPE"))
            result = r->ap_auth_type;
        else if (strlen(var) > 4 && strcEQn(var, "SSL_", 4))
            result = ssl_var_lookup_ssl(p, c, var+4);
        else if (strcEQ(var, "HTTPS")) {
            if (sslconn->ssl != NULL)
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
            result = (char *)ap_get_server_version();
        else if (strcEQ(var, "API_VERSION")) {
            result = apr_psprintf(p, "%d", MODULE_MAGIC_NUMBER);
            resdup = FALSE;
        }
        else if (strcEQ(