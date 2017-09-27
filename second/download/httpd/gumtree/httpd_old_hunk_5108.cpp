#endif
    u_long zero = 0;

    core_sconf = ap_get_core_module_config(ap_server_conf->module_config);
    accf_name = apr_table_get(core_sconf->accf_map, lr->protocol);

    if (strcmp(accf_name, "data") == 0)
        accf = 2;
    else if (strcmp(accf_name, "connect") == 0)
        accf = 1;
    else if (strcmp(accf_name, "none") == 0)
        accf = 0;
    else {
