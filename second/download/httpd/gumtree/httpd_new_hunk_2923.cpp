    apr_status_t rv;

    filename = ap_server_root_relative(cmd->temp_pool, filename);
    rv = ap_pcfg_openfile(&cfp, cmd->temp_pool, filename);
    if (rv != APR_SUCCESS) {
        return apr_psprintf(cmd->pool, "%s: Could not open file %s: %s",
                            cmd->cmd->name, filename,
                            apr_strerror(rv, lbuf, sizeof(lbuf)));
    }

    while (!(ap_cfg_getline(lbuf, MAX_STRING_LEN, cfp))) {
        args = lbuf;
        while (*(arg = ap_getword_conf(cmd->temp_pool, &args)) != '\0') {
            if (*arg == '#' || *arg == '\0') {
                break;
            }
            errmsg = proxies_set(cmd, cfg, arg);
            if (errmsg) {
                errmsg = apr_psprintf(cmd->pool, "%s at line %d of %s",
                                      errmsg, cfp->line_number, filename);
                return errmsg;
            }
        }
    }

    ap_cfg_closefile(cfp);
    return NULL;
}

static int remoteip_modify_request(request_rec *r)
{
    conn_rec *c = r->connection;
    remoteip_config_t *config = (remoteip_config_t *)
        ap_get_module_config(r->server->module_config, &remoteip_module);
    remoteip_req_t *req = NULL;

    apr_sockaddr_t *temp_sa;

    apr_status_t rv;
    char *remote;
    char *proxy_ips = NULL;
    char *parse_remote;
    char *eos;
    unsigned char *addrbyte;
    void *internal = NULL;

    if (!config->header_name) {
        return DECLINED;
    }

    remote = (char *) apr_table_get(r->headers_in, config->header_name);
    if (!remote) {
        return OK;
    }
    remote = apr_pstrdup(r->pool, remote);

    temp_sa = c->client_addr;

    while (remote) {

        /* verify c->client_addr is trusted if there is a trusted proxy list
         */
        if (config->proxymatch_ip) {
            int i;
            remoteip_proxymatch_t *match;
            match = (remoteip_proxymatch_t *)config->proxymatch_ip->elts;
            for (i = 0; i < config->proxymatch_ip->nelts; ++i) {
                if (apr_ipsubnet_test(match[i].ip, c->client_addr)) {
                    internal = match[i].internal;
                    break;
                }
            }
            if (i && i >= config->proxymatch_ip->nelts) {
                break;
            }
        }

        if ((parse_remote = strrchr(remote, ',')) == NULL) {
            parse_remote = remote;
            remote = NULL;
        }
        else {
            *(parse_remote++) = '\0';
        }

        while (*parse_remote == ' ') {
            ++parse_remote;
        }

        eos = parse_remote + strlen(parse_remote) - 1;
        while (eos >= parse_remote && *eos == ' ') {
            *(eos--) = '\0';
        }

        if (eos < parse_remote) {
            if (remote) {
                *(remote + strlen(remote)) = ',';
            }
            else {
                remote = parse_remote;
            }
            break;
        }

        /* We map as IPv4 rather than IPv6 for equivilant host names
         * or IPV4OVERIPV6
         */
        rv = apr_sockaddr_info_get(&temp_sa,  parse_remote,
                                   APR_UNSPEC, temp_sa->port,
                                   APR_IPV4_ADDR_OK, r->pool);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG,  rv, r, APLOGNO(01568)
                          "RemoteIP: Header %s value of %s cannot be parsed "
                          "as a client IP",
                          config->header_name, parse_remote);

            if (remote) {
                *(remote + strlen(remote)) = ',';
            }
            else {
                remote = parse_remote;
            }
            break;

        }

        addrbyte = (unsigned char *) &temp_sa->sa.sin.sin_addr;

        /* For intranet (Internal proxies) ignore all restrictions below */
        if (!internal
