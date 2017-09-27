    /* note that stderr may still need to be replaced with something
     * because it points to the old error log, or back to the tty
     * of the submitter.
     * XXX: This is BS - /dev/null is non-portable
     *      errno-as-apr_status_t is also non-portable
     */

#ifdef WIN32
#define NULL_DEVICE "nul"
#else
#define NULL_DEVICE "/dev/null"
#endif

    if (replace_stderr && freopen(NULL_DEVICE, "w", stderr) == NULL) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, s_main, APLOGNO(00093)
                     "unable to replace stderr with %s", NULL_DEVICE);
    }

    for (virt = s_main->next; virt; virt = virt->next) {
        if (virt->error_fname) {
            for (q=s_main; q != virt; q = q->next) {
                if (q->error_fname != NULL
