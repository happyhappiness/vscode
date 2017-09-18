static void clean_child_exit(int code) __attribute__ ((noreturn));
static void clean_child_exit(int code)
{
    if (pchild) {
        apr_pool_destroy(pchild);
    }
    exit(code);
}

/* handle all varieties of core dumping signals */
static void sig_coredump(int sig)
{
    apr_filepath_set(ap_coredump_dir, pconf);
    apr_signal(sig, SIG_DFL);
    if (ap_my_pid == parent_pid) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE,
                     0, ap_server_conf,
                     "seg fault or similar nasty error detected "
                     "in the parent process");
        
        /* XXX we can probably add some rudimentary cleanup code here,
         * like getting rid of the pid file.  If any additional bad stuff
