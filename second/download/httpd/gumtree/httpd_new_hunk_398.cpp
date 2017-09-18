    /* This could be called from an AddModule httpd.conf command,
     * after the file has been linked and the module structure within it
     * teased out...
     */

    if (m->version != MODULE_MAGIC_NUMBER_MAJOR) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "%s: module \"%s\" is not compatible with this "
                     "version of Apache.", ap_server_argv0, m->name);
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "Please contact the vendor for the correct version.");
        exit(1);
    }

    if (m->next == NULL) {
        m->next = ap_top_module;
