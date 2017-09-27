            * close(sd2) here should be okay, as CGI channel
            * is already dup()ed by apr_procattr_child_{in,out}_set()
            * above.
            */
            close(sd2);

            rc = ap_os_create_privileged_process(r, procnew, argv0, argv, 
                                                 (const char * const *)env, 
                                                 procattr, ptrans);

            if (rc != APR_SUCCESS) {
                /* Bad things happened. Everyone should have cleaned up.
                 * ap_log_rerror() won't work because the header table used by
                 * ap_log_rerror() hasn't been replicated in the phony r
                 */
                ap_log_error(APLOG_MARK, APLOG_ERR, rc, r->server,
