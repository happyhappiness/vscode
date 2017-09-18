        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't unlink unix domain socket %s",
                     sconf->sockname);
        /* just a warning; don't bail out */
    }

    /* cgid should use its own suexec doer */
    ap_hook_get_suexec_identity(cgid_suexec_id_doer, NULL, NULL,
                                APR_HOOK_REALLY_FIRST);
    apr_hook_sort_all();

    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, 
                     "Couldn't create unix domain socket");
        return errno;
    } 

