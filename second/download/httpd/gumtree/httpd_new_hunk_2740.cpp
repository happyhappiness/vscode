    /* cgid should use its own suexec doer */
    ap_hook_get_suexec_identity(cgid_suexec_id_doer, NULL, NULL,
                                APR_HOOK_REALLY_FIRST);
    apr_hook_sort_all();

    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, APLOGNO(01242)
                     "Couldn't create unix domain socket");
        return errno;
    }

    omask = umask(0077); /* so that only Apache can use socket */
    rc = bind(sd, (struct sockaddr *)server_addr, server_addr_len);
    umask(omask); /* can't fail, so can't clobber errno */
    if (rc < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, APLOGNO(01243)
                     "Couldn't bind unix domain socket %s",
                     sockname);
        return errno;
    }

    /* Not all flavors of unix use the current umask for AF_UNIX perms */
    rv = apr_file_perms_set(sockname, APR_FPROT_UREAD|APR_FPROT_UWRITE|APR_FPROT_UEXECUTE);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, main_server, APLOGNO(01244)
                     "Couldn't set permissions on unix domain socket %s",
                     sockname);
        return rv;
    }

    if (listen(sd, DEFAULT_CGID_LISTENBACKLOG) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, APLOGNO(01245)
                     "Couldn't listen on unix domain socket");
        return errno;
    }

    if (!geteuid()) {
        if (chown(sockname, ap_unixd_config.user_id, -1) < 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, APLOGNO(01246)
                         "Couldn't change owner of unix domain socket %s",
                         sockname);
            return errno;
        }
    }

