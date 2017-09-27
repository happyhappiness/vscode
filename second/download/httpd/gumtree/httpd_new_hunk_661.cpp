    r = vr;

    /* sure we got r, but don't call ap_log_rerror() because we don't
     * have r->headers_in and possibly other storage referenced by
     * ap_log_rerror()
     */
    ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server, "%s", description);
}

static int cgid_server(void *data)
{
    struct sockaddr_un unix_addr;
    int sd, sd2, rc;
    mode_t omask;
    apr_socklen_t len;
    apr_pool_t *ptrans;
    server_rec *main_server = data;
    apr_hash_t *script_hash = apr_hash_make(pcgi);

    apr_pool_create(&ptrans, pcgi);

    apr_signal(SIGCHLD, SIG_IGN);
    apr_signal(SIGHUP, daemon_signal_handler);

    /* Close our copy of the listening sockets */
    ap_close_listeners();

    /* cgid should use its own suexec doer */
    ap_hook_get_suexec_identity(cgid_suexec_id_doer, NULL, NULL,
                                APR_HOOK_REALLY_FIRST);
    apr_hook_sort_all();

    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't create unix domain socket");
        return errno;
    }

    memset(&unix_addr, 0, sizeof(unix_addr));
    unix_addr.sun_family = AF_UNIX;
    apr_cpystrn(unix_addr.sun_path, sockname, sizeof unix_addr.sun_path);

    omask = umask(0077); /* so that only Apache can use socket */
    rc = bind(sd, (struct sockaddr *)&unix_addr, sizeof(unix_addr));
    umask(omask); /* can't fail, so can't clobber errno */
    if (rc < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't bind unix domain socket %s",
                     sockname);
        return errno;
    }

    if (listen(sd, DEFAULT_CGID_LISTENBACKLOG) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't listen on unix domain socket");
        return errno;
    }

    if (!geteuid()) {
        if (chown(sockname, unixd_config.user_id, -1) < 0) {
            ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                         "Couldn't change owner of unix domain socket %s",
                         sockname);
            return errno;
        }
    }

    unixd_setup_child(); /* if running as root, switch to configured user/group */

    while (!daemon_should_exit) {
        int errfileno = STDERR_FILENO;
        char *argv0;
        char **env;
        const char * const *argv;
        apr_int32_t in_pipe;
        apr_int32_t out_pipe;
        apr_int32_t err_pipe;
        apr_cmdtype_e cmd_type;
        request_rec *r;
        apr_procattr_t *procattr = NULL;
