static const char* find_accf_name(server_rec *s, const char *proto)
{
    const char* accf;
    core_server_config *conf = ap_get_module_config(s->module_config,
                                                    &core_module);
    if (!proto) {
        return NULL;
    }

    accf = apr_table_get(conf->accf_map, proto);

    if (accf && !strcmp("none", accf)) {
        return NULL;
    }

    return accf;
}