static int show_server_settings(request_rec * r)
{
    server_rec *serv = r->server;
    int max_daemons, forked, threaded;

    ap_rputs("<h2><a name=\"server\">Server Settings</a></h2>", r);
    ap_rprintf(r,
               "<dl><dt><strong>Server Version:</strong> "
               "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
               ap_get_server_description());
    ap_rprintf(r,
               "<dt><strong>Server Built:</strong> "
               "<font size=\"+1\"><tt>%s</tt></font></dt>\n",
               ap_get_server_built());
    ap_rprintf(r,
               "<dt><strong>Server loaded APR Version:</strong> "
               "<tt>%s</tt></dt>\n", apr_version_string());
    ap_rprintf(r,
               "<dt><strong>Compiled with APR Version:</strong> "
               "<tt>%s</tt></dt>\n", APR_VERSION_STRING);
    ap_rprintf(r,
               "<dt><strong>Server loaded APU Version:</strong> "
               "<tt>%s</tt></dt>\n", apu_version_string());
    ap_rprintf(r,
               "<dt><strong>Compiled with APU Version:</strong> "
               "<tt>%s</tt></dt>\n", APU_VERSION_STRING);
    ap_rprintf(r,
               "<dt><strong>Module Magic Number:</strong> "
               "<tt>%d:%d</tt></dt>\n", MODULE_MAGIC_NUMBER_MAJOR,
               MODULE_MAGIC_NUMBER_MINOR);
    ap_rprintf(r,
               "<dt><strong>Hostname/port:</strong> "
               "<tt>%s:%u</tt></dt>\n",
               ap_escape_html(r->pool, ap_get_server_name(r)),
               ap_get_server_port(r));
    ap_rprintf(r,
               "<dt><strong>Timeouts:</strong> "
               "<tt>connection: %d &nbsp;&nbsp; "
               "keep-alive: %d</tt></dt>",
               (int) (apr_time_sec(serv->timeout)),
               (int) (apr_time_sec(serv->keep_alive_timeout)));
    ap_mpm_query(AP_MPMQ_MAX_DAEMON_USED, &max_daemons);
    ap_mpm_query(AP_MPMQ_IS_THREADED, &threaded);
    ap_mpm_query(AP_MPMQ_IS_FORKED, &forked);
    ap_rprintf(r, "<dt><strong>MPM Name:</strong> <tt>%s</tt></dt>\n",
               ap_show_mpm());
    ap_rprintf(r,
               "<dt><strong>MPM Information:</strong> "
               "<tt>Max Daemons: %d Threaded: %s Forked: %s</tt></dt>\n",
               max_daemons, threaded ? "yes" : "no", forked ? "yes" : "no");
    ap_rprintf(r,
               "<dt><strong>Server Architecture:</strong> "
               "<tt>%ld-bit</tt></dt>\n", 8 * (long) sizeof(void *));
    ap_rprintf(r,
               "<dt><strong>Server Root:</strong> "
               "<tt>%s</tt></dt>\n", ap_server_root);
    ap_rprintf(r,
               "<dt><strong>Config File:</strong> "
               "<tt>%s</tt></dt>\n", ap_conftree->filename);

    ap_rputs("<dt><strong>Server Built With:</strong>\n"
             "<tt style=\"white-space: pre;\">\n", r);

    /* TODO: Not all of these defines are getting set like they do in main.c.
     *       Missing some headers?
     */

#ifdef BIG_SECURITY_HOLE
    ap_rputs(" -D BIG_SECURITY_HOLE\n", r);
#endif

#ifdef SECURITY_HOLE_PASS_AUTHORIZATION
    ap_rputs(" -D SECURITY_HOLE_PASS_AUTHORIZATION\n", r);
#endif

#ifdef OS
    ap_rputs(" -D OS=\"" OS "\"\n", r);
#endif

#ifdef APACHE_MPM_DIR
    ap_rputs(" -D APACHE_MPM_DIR=\"" APACHE_MPM_DIR "\"\n", r);
#endif

#ifdef HAVE_SHMGET
    ap_rputs(" -D HAVE_SHMGET\n", r);
#endif

#if APR_FILE_BASED_SHM
    ap_rputs(" -D APR_FILE_BASED_SHM\n", r);
#endif

#if APR_HAS_SENDFILE
    ap_rputs(" -D APR_HAS_SENDFILE\n", r);
#endif

#if APR_HAS_MMAP
    ap_rputs(" -D APR_HAS_MMAP\n", r);
#endif

#ifdef NO_WRITEV
    ap_rputs(" -D NO_WRITEV\n", r);
#endif

#ifdef NO_LINGCLOSE
    ap_rputs(" -D NO_LINGCLOSE\n", r);
#endif

#if APR_HAVE_IPV6
    ap_rputs(" -D APR_HAVE_IPV6 (IPv4-mapped addresses ", r);
#ifdef AP_ENABLE_V4_MAPPED
    ap_rputs("enabled)\n", r);
#else
    ap_rputs("disabled)\n", r);
#endif
#endif

#if APR_USE_FLOCK_SERIALIZE
    ap_rputs(" -D APR_USE_FLOCK_SERIALIZE\n", r);
#endif

#if APR_USE_SYSVSEM_SERIALIZE
    ap_rputs(" -D APR_USE_SYSVSEM_SERIALIZE\n", r);
#endif

#if APR_USE_POSIXSEM_SERIALIZE
    ap_rputs(" -D APR_USE_POSIXSEM_SERIALIZE\n", r);
#endif

#if APR_USE_FCNTL_SERIALIZE
    ap_rputs(" -D APR_USE_FCNTL_SERIALIZE\n", r);
#endif

#if APR_USE_PROC_PTHREAD_SERIALIZE
    ap_rputs(" -D APR_USE_PROC_PTHREAD_SERIALIZE\n", r);
#endif
#if APR_PROCESS_LOCK_IS_GLOBAL
    ap_rputs(" -D APR_PROCESS_LOCK_IS_GLOBAL\n", r);
#endif

#ifdef SINGLE_LISTEN_UNSERIALIZED_ACCEPT
    ap_rputs(" -D SINGLE_LISTEN_UNSERIALIZED_ACCEPT\n", r);
#endif

#if APR_HAS_OTHER_CHILD
    ap_rputs(" -D APR_HAS_OTHER_CHILD\n", r);
#endif

#ifdef AP_HAVE_RELIABLE_PIPED_LOGS
    ap_rputs(" -D AP_HAVE_RELIABLE_PIPED_LOGS\n", r);
#endif

#ifdef BUFFERED_LOGS
    ap_rputs(" -D BUFFERED_LOGS\n", r);
#ifdef PIPE_BUF
    ap_rputs(" -D PIPE_BUF=%ld\n", (long) PIPE_BUF, r);
#endif
#endif

#if APR_CHARSET_EBCDIC
    ap_rputs(" -D APR_CHARSET_EBCDIC\n", r);
#endif

#ifdef NEED_HASHBANG_EMUL
    ap_rputs(" -D NEED_HASHBANG_EMUL\n", r);
#endif

#ifdef SHARED_CORE
    ap_rputs(" -D SHARED_CORE\n", r);
#endif

/* This list displays the compiled in default paths: */
#ifdef HTTPD_ROOT
    ap_rputs(" -D HTTPD_ROOT=\"" HTTPD_ROOT "\"\n", r);
#endif

#ifdef SUEXEC_BIN
    ap_rputs(" -D SUEXEC_BIN=\"" SUEXEC_BIN "\"\n", r);
#endif

#if defined(SHARED_CORE) && defined(SHARED_CORE_DIR)
    ap_rputs(" -D SHARED_CORE_DIR=\"" SHARED_CORE_DIR "\"\n", r);
#endif

#ifdef DEFAULT_PIDLOG
    ap_rputs(" -D DEFAULT_PIDLOG=\"" DEFAULT_PIDLOG "\"\n", r);
#endif

#ifdef DEFAULT_SCOREBOARD
    ap_rputs(" -D DEFAULT_SCOREBOARD=\"" DEFAULT_SCOREBOARD "\"\n", r);
#endif

#ifdef DEFAULT_LOCKFILE
    ap_rputs(" -D DEFAULT_LOCKFILE=\"" DEFAULT_LOCKFILE "\"\n", r);
#endif

#ifdef DEFAULT_ERRORLOG
    ap_rputs(" -D DEFAULT_ERRORLOG=\"" DEFAULT_ERRORLOG "\"\n", r);
#endif


#ifdef AP_TYPES_CONFIG_FILE
    ap_rputs(" -D AP_TYPES_CONFIG_FILE=\"" AP_TYPES_CONFIG_FILE "\"\n", r);
#endif

#ifdef SERVER_CONFIG_FILE
    ap_rputs(" -D SERVER_CONFIG_FILE=\"" SERVER_CONFIG_FILE "\"\n", r);
#endif
    ap_rputs("</tt></dt>\n", r);
    ap_rputs("</dl><hr />", r);
    return 0;
}