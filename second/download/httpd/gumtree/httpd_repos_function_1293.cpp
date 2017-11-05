static int mva_translate(request_rec *r)
{
    mva_sconf_t *conf;
    const char *name, *map, *uri;
    mva_mode_e mode;
    const char *cgi;

    conf = (mva_sconf_t *) ap_get_module_config(r->server->module_config,
                                              &vhost_alias_module);
    cgi = NULL;
    if (conf->cgi_root) {
        cgi = strstr(r->uri, "cgi-bin/");
        if (cgi && (cgi != r->uri + strspn(r->uri, "/"))) {
            cgi = NULL;
        }
    }
    if (cgi) {
        mode = conf->cgi_root_mode;
        map = conf->cgi_root;
        uri = cgi + strlen("cgi-bin");
    }
    else if (r->uri[0] == '/') {
        mode = conf->doc_root_mode;
        map = conf->doc_root;
        uri = r->uri;
    }
    else {
        return DECLINED;
    }

    if (mode == VHOST_ALIAS_NAME) {
        name = ap_get_server_name(r);
    }
    else if (mode == VHOST_ALIAS_IP) {
        name = r->connection->local_ip;
    }
    else {
        return DECLINED;
    }

    /* ### There is an optimization available here to determine the
     * absolute portion of the path from the server config phase,
     * through the first % segment, and note that portion of the path
     * canonical_path buffer.
     */
    r->canonical_filename = "";
    vhost_alias_interpolate(r, name, map, uri);

    if (cgi) {
        /* see is_scriptaliased() in mod_cgi */
        r->handler = "cgi-script";
        apr_table_setn(r->notes, "alias-forced-type", r->handler);
    }

    return OK;
}