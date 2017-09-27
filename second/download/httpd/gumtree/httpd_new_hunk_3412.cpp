     *     The -d serverroot default from the running executable
     *         The requested service's (-n) registry ConfigArgs
     *             The WinNT SCM's StartService() args
     */
    if ((rv = ap_os_proc_filepath(&binpath, process->pconf))
            != APR_SUCCESS) {
        ap_log_error(APLOG_MARK,APLOG_CRIT, rv, NULL, APLOGNO(00432)
                     "Failed to get the full path of %s", process->argv[0]);
        exit(APEXIT_INIT);
    }
    /* WARNING: There is an implict assumption here that the
     * executable resides in ServerRoot or ServerRoot\bin
     */
