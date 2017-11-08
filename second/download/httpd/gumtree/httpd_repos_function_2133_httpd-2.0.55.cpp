static void chdir_for_gprof(void)
{
    core_server_config *sconf = 
	ap_get_module_config(ap_server_conf->module_config, &core_module);    
    char *dir = sconf->gprof_dir;
    const char *use_dir;

    if(dir) {
        apr_status_t res;
	char buf[512];
	int len = strlen(sconf->gprof_dir) - 1;
	if(*(dir + len) == '%') {
	    dir[len] = '\0';
	    apr_snprintf(buf, sizeof(buf), "%sgprof.%d", dir, (int)getpid());
	} 
	use_dir = ap_server_root_relative(pconf, buf[0] ? buf : dir);
	res = apr_dir_make(use_dir, 0755, pconf);
	if(res != APR_SUCCESS && !APR_STATUS_IS_EEXIST(res)) {
	    ap_log_error(APLOG_MARK, APLOG_ERR, errno, ap_server_conf,
			 "gprof: error creating directory %s", dir);
	}
    }
    else {
	use_dir = ap_server_root_relative(pconf, DEFAULT_REL_RUNTIMEDIR);
    }

    chdir(use_dir);
}