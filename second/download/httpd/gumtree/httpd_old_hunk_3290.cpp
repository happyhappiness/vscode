     * because it points to the old error log, or back to the tty
     * of the submitter.
     * XXX: This is BS - /dev/null is non-portable
     *      errno-as-apr_status_t is also non-portable
     */
    if (replace_stderr && freopen("/dev/null", "w", stderr) == NULL) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, errno, s_main,
                     "unable to replace stderr with /dev/null");
    }

    for (virt = s_main->next; virt; virt = virt->next) {
        if (virt->error_fname) {
            for (q=s_main; q != virt; q = q->next) {
