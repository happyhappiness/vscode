     *
     * The invocation command (%0)
     *     The -d serverroot default from the running executable
     *         The requested service's (-n) registry ConfigArgs
     *             The WinNT SCM's StartService() args
     */
    if (!GetModuleFileName(NULL, fnbuf, sizeof(fnbuf))) {
        rv = apr_get_os_error();
        ap_log_error(APLOG_MARK,APLOG_CRIT, rv, NULL, 
                     "Failed to get the path of Apache.exe");
        exit(APEXIT_INIT);
    }
    /* WARNING: There is an implict assumption here that the
     * executable resides in ServerRoot or ServerRoot\bin
     */
    def_server_root = (char *) apr_filename_of_pathname(fnbuf);
    if (def_server_root > fnbuf) {
        *(def_server_root - 1) = '\0';
        def_server_root = (char *) apr_filename_of_pathname(fnbuf);
        if (!strcasecmp(def_server_root, "bin"))
            *(def_server_root - 1) = '\0';
    }
    apr_filepath_merge(&def_server_root, NULL, fnbuf, 
                       APR_FILEPATH_TRUENAME, process->pool);

    /* Use process->pool so that the rewritten argv
     * lasts for the lifetime of the server process,
     * because pconf will be destroyed after the 
     * initial pre-flight of the config parser.
