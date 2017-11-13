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
        apr_proc_t *procnew = NULL;
        apr_file_t *inout;
        cgid_req_t cgid_req;
        apr_status_t stat;

        apr_pool_clear(ptrans);

        len = sizeof(unix_addr);
        sd2 = accept(sd, (struct sockaddr *)&unix_addr, &len);
        if (sd2 < 0) {
#if defined(ENETDOWN)
            if (errno == ENETDOWN) {
                /* The network has been shut down, no need to continue. Die gracefully */
                ++daemon_should_exit;
            }
#endif
            if (errno != EINTR) {
                ap_log_error(APLOG_MARK, APLOG_ERR, errno,
                             (server_rec *)data,
                             "Error accepting on cgid socket");
            }
            continue;
        }

        r = apr_pcalloc(ptrans, sizeof(request_rec));
        procnew = apr_pcalloc(ptrans, sizeof(*procnew));
        r->pool = ptrans;
        stat = get_req(sd2, r, &argv0, &env, &cgid_req);
        if (stat != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, stat,
                         main_server,
                         "Error reading request on cgid socket");
            close(sd2);
            continue;
        }

        if (cgid_req.ppid != parent_pid) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, main_server,
                         "CGI request received from wrong server instance; "
                         "see ScriptSock directive");
            close(sd2);
            continue;
        }

        if (cgid_req.req_type == GETPID_REQ) {
            pid_t pid;

            pid = (pid_t)((long)apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id)));
            if (write(sd2, &pid, sizeof(pid)) != sizeof(pid)) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                             main_server,
                             "Error writing pid %" APR_PID_T_FMT " to handler", pid);
            }
            close(sd2);
            continue;
        }

        apr_os_file_put(&r->server->error_log, &errfileno, 0, r->pool);
        apr_os_file_put(&inout, &sd2, 0, r->pool);

        if (cgid_req.req_type == SSI_REQ) {
            in_pipe  = APR_NO_PIPE;
            out_pipe = APR_FULL_BLOCK;
            err_pipe = APR_NO_PIPE;
            cmd_type = APR_SHELLCMD;
        }
        else {
            in_pipe  = APR_CHILD_BLOCK;
            out_pipe = APR_CHILD_BLOCK;
            err_pipe = APR_CHILD_BLOCK;
            cmd_type = APR_PROGRAM;
        }

        if (((rc = apr_procattr_create(&procattr, ptrans)) != APR_SUCCESS) ||
            ((cgid_req.req_type == CGI_REQ) &&
             (((rc = apr_procattr_io_set(procattr,
                                        in_pipe,
                                        out_pipe,
                                        err_pipe)) != APR_SUCCESS) ||
              /* XXX apr_procattr_child_*_set() is creating an unnecessary
               * pipe between this process and the child being created...
               * It is cleaned up with the temporary pool for this request.
               */
              ((rc = apr_procattr_child_err_set(procattr, r->server->error_log, NULL)) != APR_SUCCESS) ||
              ((rc = apr_procattr_child_in_set(procattr, inout, NULL)) != APR_SUCCESS))) ||
            ((rc = apr_procattr_child_out_set(procattr, inout, NULL)) != APR_SUCCESS) ||
            ((rc = apr_procattr_dir_set(procattr,
                                  ap_make_dirstr_parent(r->pool, r->filename))) != APR_SUCCESS) ||
            ((rc = apr_procattr_cmdtype_set(procattr, cmd_type)) != APR_SUCCESS) ||
            ((rc = apr_procattr_child_errfn_set(procattr, cgid_child_errfn)) != APR_SUCCESS)) {
            /* Something bad happened, tell the world.
             * ap_log_rerror() won't work because the header table used by
             * ap_log_rerror() hasn't been replicated in the phony r
             */
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                         "couldn't set child process attributes: %s", r->filename);
        }
        else {
            apr_pool_userdata_set(r, ERRFN_USERDATA_KEY, apr_pool_cleanup_null, ptrans);

            argv = (const char * const *)create_argv(r->pool, NULL, NULL, NULL, argv0, r->args);

           /* We want to close sd2 for the new CGI process too.
            * If it is left open it'll make ap_pass_brigade() block
            * waiting for EOF if CGI forked something running long.
            * close(sd2) here should be okay, as CGI channel
            * is already dup()ed by apr_procattr_child_{in,out}_set()
            * above.
            */
            close(sd2);

            if (memcmp(&empty_ugid, &cgid_req.ugid, sizeof(empty_ugid))) {
                /* We have a valid identity, and can be sure that
                 * cgid_suexec_id_doer will return a valid ugid
                 */
                rc = ap_os_create_privileged_process(r, procnew, argv0, argv,
                                                     (const char * const *)env,
                                                     procattr, ptrans);
            } else {
                rc = apr_proc_create(procnew, argv0, argv,
                                     (const char * const *)env,
                                     procattr, ptrans);
            }

            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up.
                 * ap_log_rerror() won't work because the header table used by
                 * ap_log_rerror() hasn't been replicated in the phony r
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
                             "couldn't create child process: %d: %s", rc,
                             apr_filepath_name_get(r->filename));
            }
            else {
                /* We don't want to leak storage for the key, so only allocate
                 * a key if the key doesn't exist yet in the hash; there are
                 * only a limited number of possible keys (one for each
                 * possible thread in the server), so we can allocate a copy
                 * of the key the first time a thread has a cgid request.
                 * Note that apr_hash_set() only uses the storage passed in
                 * for the key if it is adding the key to the hash for the
                 * first time; new key storage isn't needed for replacing the
                 * existing value of a key.
                 */
                void *key;

                if (apr_hash_get(script_hash, &cgid_req.conn_id, sizeof(cgid_req.conn_id))) {
                    key = &cgid_req.conn_id;
                }
                else {
                    key = apr_pcalloc(pcgi, sizeof(cgid_req.conn_id));
                    memcpy(key, &cgid_req.conn_id, sizeof(cgid_req.conn_id));
                }
                apr_hash_set(script_hash, key, sizeof(cgid_req.conn_id),
                             (void *)((long)procnew->pid));
            }
        }
    }
    return -1;
}