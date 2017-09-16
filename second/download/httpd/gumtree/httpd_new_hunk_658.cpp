#else

    mode_t rewritelog_mode  = ( S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH );

#endif



    conf = ap_get_module_config(s->module_config, &rewrite_module);



    if (conf->rewritelogfile == NULL) {

        return;

    }

    if (*(conf->rewritelogfile) == '\0') {

        return;

    }

    if (conf->rewritelogfp > 0) {

        return; /* virtual log shared w/ main server */

    }



    fname = ap_server_root_relative(p, conf->rewritelogfile);



    if (*conf->rewritelogfile == '|') {

        if ((pl = ap_open_piped_log(p, conf->rewritelogfile+1)) == NULL) {

            ap_log_error(APLOG_MARK, APLOG_ERR, s, 

