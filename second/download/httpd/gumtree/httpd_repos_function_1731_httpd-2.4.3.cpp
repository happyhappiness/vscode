static const char *
    set_allowed_ports(cmd_parms *parms, void *dummy, const char *arg)
{
    server_rec *s = parms->server;
    int first, last;
    connect_conf *conf =
        ap_get_module_config(s->module_config, &proxy_connect_module);
    port_range *New;
    char *endptr;
    const char *p = arg;

    if (!apr_isdigit(arg[0]))
        return "AllowCONNECT: port numbers must be numeric";

    first = strtol(p, &endptr, 10);
    if (*endptr == '-') {
        p = endptr + 1;
        last = strtol(p, &endptr, 10);
    }
    else {
        last = first;
    }

    if (endptr == p || *endptr != '\0')  {
        return apr_psprintf(parms->temp_pool,
                            "Cannot parse '%s' as port number", p);
    }

    New = apr_array_push(conf->allowed_connect_ports);
    New->first = first;
    New->last  = last;
    return NULL;
}