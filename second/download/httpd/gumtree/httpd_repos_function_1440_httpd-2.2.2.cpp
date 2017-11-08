static const char *
    add_proxy(cmd_parms *cmd, void *dummy, const char *f1, const char *r1, int regex)
{
    server_rec *s = cmd->server;
    proxy_server_conf *conf =
    (proxy_server_conf *) ap_get_module_config(s->module_config, &proxy_module);
    struct proxy_remote *new;
    char *p, *q;
    char *r, *f, *scheme;
    ap_regex_t *reg = NULL;
    int port;

    r = apr_pstrdup(cmd->pool, r1);
    scheme = apr_pstrdup(cmd->pool, r1);
    f = apr_pstrdup(cmd->pool, f1);
    p = strchr(r, ':');
    if (p == NULL || p[1] != '/' || p[2] != '/' || p[3] == '\0') {
        if (regex)
            return "ProxyRemoteMatch: Bad syntax for a remote proxy server";
        else
            return "ProxyRemote: Bad syntax for a remote proxy server";
    }
    else {
        scheme[p-r] = 0;
    }
    q = strchr(p + 3, ':');
    if (q != NULL) {
        if (sscanf(q + 1, "%u", &port) != 1 || port > 65535) {
            if (regex)
                return "ProxyRemoteMatch: Bad syntax for a remote proxy server (bad port number)";
            else
                return "ProxyRemote: Bad syntax for a remote proxy server (bad port number)";
        }
        *q = '\0';
    }
    else
        port = -1;
    *p = '\0';
    if (regex) {
        reg = ap_pregcomp(cmd->pool, f, AP_REG_EXTENDED);
        if (!reg)
            return "Regular expression for ProxyRemoteMatch could not be compiled.";
    }
    else
        if (strchr(f, ':') == NULL)
            ap_str_tolower(f);      /* lowercase scheme */
    ap_str_tolower(p + 3);      /* lowercase hostname */

    if (port == -1) {
        port = apr_uri_port_of_scheme(scheme);
    }

    new = apr_array_push(conf->proxies);
    new->scheme = f;
    new->protocol = r;
    new->hostname = p + 3;
    new->port = port;
    new->regexp = reg;
    new->use_regex = regex;
    return NULL;
}