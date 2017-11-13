static void chdir_for_gprof(void)
{
    core_server_config *sconf =
        ap_get_module_config(ap_server_conf->module_config, &core_module);
    char *dir = sconf->gprof_dir;
    const char *use_dir;

    if(dir) {
        apr_status_t res;
        char *buf = NULL ;
        int len = strlen(sconf->gprof_dir) - 1;
        if(*(dir + len) == '%') {
            dir[len] = '\0';
            buf = ap_append_pid(pconf, dir, "gprof.");
        }
        use_dir = ap_server_root_relative(pconf, buf ? buf : dir);
        res = apr_dir_make(use_dir,
                           APR_UREAD | APR_UWRITE | APR_UEXECUTE |
                           APR_GREAD | APR_GEXECUTE |
                           APR_WREAD | APR_WEXECUTE, pconf);
        if(res != APR_SUCCESS && !APR_STATUS_IS_EEXIST(res)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, res, ap_server_conf,
                         "gprof: error creating directory %s", dir);
        }
    }
    else {
        use_dir = ap_server_root_relative(pconf, DEFAULT_REL_RUNTIMEDIR);
    }

    chdir(use_dir);
}