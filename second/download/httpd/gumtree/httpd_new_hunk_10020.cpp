                                         REWRITELOCK_MODE)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, s,
                     "mod_rewrite: Parent could not create RewriteLock "
                     "file %s", conf->rewritelockfile);
        exit(1);
    }
#if !defined(OS2) && !defined(WIN32)
    /* make sure the childs have access to this file */
    if (geteuid() == 0 /* is superuser */)
        chown(conf->rewritelockfile, ap_user_id, -1 /* no gid change */);
#endif

    return;
