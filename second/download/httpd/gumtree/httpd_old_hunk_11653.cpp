    configfile_t *fp;
    info_cfg_lines *new, *ret, *prev;
    const char *t;

    fp = ap_pcfg_openfile(p, filename);
    if (!fp) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, r->server, 
		    "mod_info: couldn't open config file %s",
		    filename);
        return NULL;
    }
    ret = NULL;
    prev = NULL;
