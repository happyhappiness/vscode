                            " is not a directory", NULL);
     }
     apr_cpystrn(ap_coredump_dir, fname, sizeof(ap_coredump_dir));
     ap_coredumpdir_configured = 1;
     return NULL;
 }
-#endif
 
-#ifdef AP_MPM_WANT_SET_GRACEFUL_SHUTDOWN
 int ap_graceful_shutdown_timeout = 0;
 
 const char * ap_mpm_set_graceful_shutdown(cmd_parms *cmd, void *dummy,
                                           const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
     ap_graceful_shutdown_timeout = atoi(arg);
     return NULL;
 }
-#endif
-
-#ifdef AP_MPM_WANT_SET_ACCEPT_LOCK_MECH
-apr_lockmech_e ap_accept_lock_mech = APR_LOCK_DEFAULT;
-
-const char ap_valid_accept_mutex_string[] =
-    "Valid accept mutexes for this platform and MPM are: default"
-#if APR_HAS_FLOCK_SERIALIZE
-    ", flock"
-#endif
-#if APR_HAS_FCNTL_SERIALIZE
-    ", fcntl"
-#endif
-#if APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)
-    ", sysvsem"
-#endif
-#if APR_HAS_POSIXSEM_SERIALIZE
-    ", posixsem"
-#endif
-#if APR_HAS_PROC_PTHREAD_SERIALIZE
-    ", pthread"
-#endif
-    ".";
-
-AP_DECLARE(const char *) ap_mpm_set_accept_lock_mech(cmd_parms *cmd,
-                                                     void *dummy,
-                                                     const char *arg)
-{
-    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
-    if (err != NULL) {
-        return err;
-    }
-
-    if (!strcasecmp(arg, "default")) {
-        ap_accept_lock_mech = APR_LOCK_DEFAULT;
-    }
-#if APR_HAS_FLOCK_SERIALIZE
-    else if (!strcasecmp(arg, "flock")) {
-        ap_accept_lock_mech = APR_LOCK_FLOCK;
-    }
-#endif
-#if APR_HAS_FCNTL_SERIALIZE
-    else if (!strcasecmp(arg, "fcntl")) {
-        ap_accept_lock_mech = APR_LOCK_FCNTL;
-    }
-#endif
-
-    /* perchild can't use SysV sems because the permissions on the accept
-     * mutex can't be set to allow all processes to use the mutex and
-     * at the same time keep all users from being able to dink with the
-     * mutex
-     */
-#if APR_HAS_SYSVSEM_SERIALIZE && !defined(PERCHILD_MPM)
-    else if (!strcasecmp(arg, "sysvsem")) {
-        ap_accept_lock_mech = APR_LOCK_SYSVSEM;
-    }
-#endif
-#if APR_HAS_POSIXSEM_SERIALIZE
-    else if (!strcasecmp(arg, "posixsem")) {
-        ap_accept_lock_mech = APR_LOCK_POSIXSEM;
-    }
-#endif
-#if APR_HAS_PROC_PTHREAD_SERIALIZE
-    else if (!strcasecmp(arg, "pthread")) {
-        ap_accept_lock_mech = APR_LOCK_PROC_PTHREAD;
-    }
-#endif
-    else {
-        return apr_pstrcat(cmd->pool, arg, " is an invalid mutex mechanism; ",
-                           ap_valid_accept_mutex_string, NULL);
-    }
-    return NULL;
-}
-
-#endif
-
-#ifdef AP_MPM_WANT_SIGNAL_SERVER
-
-static const char *dash_k_arg;
-
-static int send_signal(pid_t pid, int sig)
-{
-    if (kill(pid, sig) < 0) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, errno, NULL,
-                     "sending signal to server");
-        return 1;
-    }
-    return 0;
-}
-
-int ap_signal_server(int *exit_status, apr_pool_t *pconf)
-{
-    apr_status_t rv;
-    pid_t otherpid;
-    int running = 0;
-    const char *status;
-
-    *exit_status = 0;
-
-    rv = ap_read_pid(pconf, ap_pid_fname, &otherpid);
-    if (rv != APR_SUCCESS) {
-        if (rv != APR_ENOENT) {
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, rv, NULL,
-                         "Error retrieving pid file %s", ap_pid_fname);
-            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                         "Remove it before continuing if it is corrupted.");
-            *exit_status = 1;
-            return 1;
-        }
-        status = "httpd (no pid file) not running";
-    }
-    else {
-        if (kill(otherpid, 0) == 0) {
-            running = 1;
-            status = apr_psprintf(pconf,
-                                  "httpd (pid %" APR_PID_T_FMT ") already "
-                                  "running", otherpid);
-        }
-        else {
-            status = apr_psprintf(pconf,
-                                  "httpd (pid %" APR_PID_T_FMT "?) not running",
-                                  otherpid);
-        }
-    }
-
-    if (!strcmp(dash_k_arg, "start")) {
-        if (running) {
-            printf("%s\n", status);
-            return 1;
-        }
-    }
-
-    if (!strcmp(dash_k_arg, "stop")) {
-        if (!running) {
-            printf("%s\n", status);
-        }
-        else {
-            send_signal(otherpid, SIGTERM);
-        }
-        return 1;
-    }
-
-    if (!strcmp(dash_k_arg, "restart")) {
-        if (!running) {
-            printf("httpd not running, trying to start\n");
-        }
-        else {
-            *exit_status = send_signal(otherpid, SIGHUP);
-            return 1;
-        }
-    }
-
-    if (!strcmp(dash_k_arg, "graceful")) {
-        if (!running) {
-            printf("httpd not running, trying to start\n");
-        }
-        else {
-            *exit_status = send_signal(otherpid, AP_SIG_GRACEFUL);
-            return 1;
-        }
-    }
-
-    if (!strcmp(dash_k_arg, "graceful-stop")) {
-#ifdef AP_MPM_WANT_SET_GRACEFUL_SHUTDOWN
-        if (!running) {
-            printf("%s\n", status);
-        }
-        else {
-            *exit_status = send_signal(otherpid, AP_SIG_GRACEFUL_STOP);
-        }
-#else
-        printf("httpd MPM \"" MPM_NAME "\" does not support graceful-stop\n");
-#endif
-        return 1;
-    }
-
-    return 0;
-}
 
-void ap_mpm_rewrite_args(process_rec *process)
-{
-    apr_array_header_t *mpm_new_argv;
-    apr_status_t rv;
-    apr_getopt_t *opt;
-    char optbuf[3];
-    const char *optarg;
-
-    mpm_new_argv = apr_array_make(process->pool, process->argc,
-                                  sizeof(const char **));
-    *(const char **)apr_array_push(mpm_new_argv) = process->argv[0];
-    apr_getopt_init(&opt, process->pool, process->argc, process->argv);
-    opt->errfn = NULL;
-    optbuf[0] = '-';
-    /* option char returned by apr_getopt() will be stored in optbuf[1] */
-    optbuf[2] = '\0';
-    while ((rv = apr_getopt(opt, "k:" AP_SERVER_BASEARGS,
-                            optbuf + 1, &optarg)) == APR_SUCCESS) {
-        switch(optbuf[1]) {
-        case 'k':
-            if (!dash_k_arg) {
-                if (!strcmp(optarg, "start") || !strcmp(optarg, "stop") ||
-                    !strcmp(optarg, "restart") || !strcmp(optarg, "graceful") ||
-                    !strcmp(optarg, "graceful-stop")) {
-                    dash_k_arg = optarg;
-                    break;
-                }
-            }
-        default:
-            *(const char **)apr_array_push(mpm_new_argv) =
-                apr_pstrdup(process->pool, optbuf);
-            if (optarg) {
-                *(const char **)apr_array_push(mpm_new_argv) = optarg;
-            }
-        }
-    }
-
-    /* back up to capture the bad argument */
-    if (rv == APR_BADCH || rv == APR_BADARG) {
-        opt->ind--;
-    }
-
-    while (opt->ind < opt->argc) {
-        *(const char **)apr_array_push(mpm_new_argv) =
-            apr_pstrdup(process->pool, opt->argv[opt->ind++]);
-    }
-
-    process->argc = mpm_new_argv->nelts;
-    process->argv = (const char * const *)mpm_new_argv->elts;
-
-    if (dash_k_arg) {
-        APR_REGISTER_OPTIONAL_FN(ap_signal_server);
-    }
-}
-
-#endif /* AP_MPM_WANT_SIGNAL_SERVER */
-
-#ifdef AP_MPM_WANT_SET_MAX_MEM_FREE
 apr_uint32_t ap_max_mem_free = APR_ALLOCATOR_MAX_FREE_UNLIMITED;
 
 const char *ap_mpm_set_max_mem_free(cmd_parms *cmd, void *dummy,
                                     const char *arg)
 {
     long value;
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    errno = 0;
     value = strtol(arg, NULL, 0);
     if (value < 0 || errno == ERANGE)
         return apr_pstrcat(cmd->pool, "Invalid MaxMemFree value: ",
                            arg, NULL);
 
     ap_max_mem_free = (apr_uint32_t)value * 1024;
 
     return NULL;
 }
 
-#endif /* AP_MPM_WANT_SET_MAX_MEM_FREE */
-
-#ifdef AP_MPM_WANT_SET_STACKSIZE
 apr_size_t ap_thread_stacksize = 0; /* use system default */
 
 const char *ap_mpm_set_thread_stacksize(cmd_parms *cmd, void *dummy,
                                         const char *arg)
 {
     long value;
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
-    errno = 0;
     value = strtol(arg, NULL, 0);
     if (value < 0 || errno == ERANGE)
         return apr_pstrcat(cmd->pool, "Invalid ThreadStackSize value: ",
                            arg, NULL);
 
     ap_thread_stacksize = (apr_size_t)value;
 
     return NULL;
 }
 
-#endif /* AP_MPM_WANT_SET_STACKSIZE */
-
-#ifdef AP_MPM_WANT_FATAL_SIGNAL_HANDLER
-
-static pid_t parent_pid, my_pid;
-apr_pool_t *pconf;
-
-#if AP_ENABLE_EXCEPTION_HOOK
-
-static int exception_hook_enabled;
-
-const char *ap_mpm_set_exception_hook(cmd_parms *cmd, void *dummy,
-                                      const char *arg)
+AP_DECLARE(apr_status_t) ap_mpm_query(int query_code, int *result)
 {
-    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
-    if (err != NULL) {
-        return err;
-    }
-
-    if (cmd->server->is_virtual) {
-        return "EnableExceptionHook directive not allowed in <VirtualHost>";
-    }
+    apr_status_t rv;
 
-    if (strcasecmp(arg, "on") == 0) {
-        exception_hook_enabled = 1;
-    }
-    else if (strcasecmp(arg, "off") == 0) {
-        exception_hook_enabled = 0;
+    if (ap_run_mpm_query(query_code, result, &rv) == DECLINED) {
+        rv = APR_EGENERAL;
     }
-    else {
-        return "parameter must be 'on' or 'off'";
-    }
-
-    return NULL;
-}
 
-static void run_fatal_exception_hook(int sig)
-{
-    ap_exception_info_t ei = {0};
-
-    if (exception_hook_enabled &&
-        geteuid() != 0 &&
-        my_pid != parent_pid) {
-        ei.sig = sig;
-        ei.pid = my_pid;
-        ap_run_fatal_exception(&ei);
-    }
+    return rv;
 }
-#endif /* AP_ENABLE_EXCEPTION_HOOK */
 
-/* handle all varieties of core dumping signals */
-static void sig_coredump(int sig)
+AP_DECLARE(apr_status_t) ap_mpm_note_child_killed(int childnum)
 {
-    apr_filepath_set(ap_coredump_dir, pconf);
-    apr_signal(sig, SIG_DFL);
-#if AP_ENABLE_EXCEPTION_HOOK
-    run_fatal_exception_hook(sig);
-#endif
-    /* linuxthreads issue calling getpid() here:
-     *   This comparison won't match if the crashing thread is
-     *   some module's thread that runs in the parent process.
-     *   The fallout, which is limited to linuxthreads:
-     *   The special log message won't be written when such a
-     *   thread in the parent causes the parent to crash.
-     */
-    if (getpid() == parent_pid) {
-        ap_log_error(APLOG_MARK, APLOG_NOTICE,
-                     0, ap_server_conf,
-                     "seg fault or similar nasty error detected "
-                     "in the parent process");
-        /* XXX we can probably add some rudimentary cleanup code here,
-         * like getting rid of the pid file.  If any additional bad stuff
-         * happens, we are protected from recursive errors taking down the
-         * system since this function is no longer the signal handler   GLA
-         */
-    }
-    kill(getpid(), sig);
-    /* At this point we've got sig blocked, because we're still inside
-     * the signal handler.  When we leave the signal handler it will
-     * be unblocked, and we'll take the signal... and coredump or whatever
-     * is appropriate for this particular Unix.  In addition the parent
-     * will see the real signal we received -- whereas if we called
-     * abort() here, the parent would only see SIGABRT.
-     */
+    return ap_run_mpm_note_child_killed(childnum);
 }
 
-apr_status_t ap_fatal_signal_child_setup(server_rec *s)
+AP_DECLARE(apr_status_t) ap_mpm_register_timed_callback(apr_time_t t, ap_mpm_callback_fn_t *cbfn, void *baton)
 {
-    my_pid = getpid();
-    return APR_SUCCESS;
+    return ap_run_mpm_register_timed_callback(t, cbfn, baton);
 }
 
-apr_status_t ap_fatal_signal_setup(server_rec *s, apr_pool_t *in_pconf)
+AP_DECLARE(const char *)ap_show_mpm(void)
 {
-#ifndef NO_USE_SIGACTION
-    struct sigaction sa;
+    const char *name = ap_run_mpm_get_name();
 
-    sigemptyset(&sa.sa_mask);
-
-#if defined(SA_ONESHOT)
-    sa.sa_flags = SA_ONESHOT;
-#elif defined(SA_RESETHAND)
-    sa.sa_flags = SA_RESETHAND;
-#else
-    sa.sa_flags = 0;
-#endif
-
-    sa.sa_handler = sig_coredump;
-    if (sigaction(SIGSEGV, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGSEGV)");
-#ifdef SIGBUS
-    if (sigaction(SIGBUS, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGBUS)");
-#endif
-#ifdef SIGABORT
-    if (sigaction(SIGABORT, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABORT)");
-#endif
-#ifdef SIGABRT
-    if (sigaction(SIGABRT, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABRT)");
-#endif
-#ifdef SIGILL
-    if (sigaction(SIGILL, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGILL)");
-#endif
-#ifdef SIGFPE
-    if (sigaction(SIGFPE, &sa, NULL) < 0)
-        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGFPE)");
-#endif
-
-#else /* NO_USE_SIGACTION */
-
-    apr_signal(SIGSEGV, sig_coredump);
-#ifdef SIGBUS
-    apr_signal(SIGBUS, sig_coredump);
-#endif /* SIGBUS */
-#ifdef SIGABORT
-    apr_signal(SIGABORT, sig_coredump);
-#endif /* SIGABORT */
-#ifdef SIGABRT
-    apr_signal(SIGABRT, sig_coredump);
-#endif /* SIGABRT */
-#ifdef SIGILL
-    apr_signal(SIGILL, sig_coredump);
-#endif /* SIGILL */
-#ifdef SIGFPE
-    apr_signal(SIGFPE, sig_coredump);
-#endif /* SIGFPE */
-
-#endif /* NO_USE_SIGACTION */
-
-    pconf = in_pconf;
-    parent_pid = my_pid = getpid();
+    if (!name) {
+        name = "";
+    }
 
-    return APR_SUCCESS;
+    return name;
 }
-
-#endif /* AP_MPM_WANT_FATAL_SIGNAL_HANDLER */
