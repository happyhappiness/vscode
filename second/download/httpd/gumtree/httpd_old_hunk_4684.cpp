    ap_init_modules(pconf, server_conf);
    ap_suexec_enabled = init_suexec();
    version_locked++;
    ap_open_logs(server_conf, pconf);
    set_group_privs();

#ifdef __EMX__
    printf("%s \n", ap_get_server_version());
#endif
#ifdef WIN32
    if (!child) {
	printf("%s \n", ap_get_server_version());
    }
