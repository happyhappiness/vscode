static int allowed_port(connect_conf *conf, int port)
{
    int i;
    port_range *list = (port_range *) conf->allowed_connect_ports->elts;

    if (apr_is_empty_array(conf->allowed_connect_ports)){
        return port == APR_URI_HTTPS_DEFAULT_PORT
               || port == APR_URI_SNEWS_DEFAULT_PORT;
    }

    for (i = 0; i < conf->allowed_connect_ports->nelts; i++) {
        if (port >= list[i].first && port <= list[i].last)
            return 1;
    }
    return 0;
}