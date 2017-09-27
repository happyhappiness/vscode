            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
            (*fpin) = procnew->in;
            /* read handle to pipe not kept open, so no need to call
             * close_handle_in_child()
             */
        }

        /* apr_procattr_child_err_set dups errfile twice: close the
         * remaining "parent-side" copy (apr_proc_create closes the
         * other). */
        if (dummy_stderr) {
            apr_file_close(procnew->err);
        }
    }

    return rc;
}

/* Open the error log for the given server_rec.  If IS_MAIN is
 * non-zero, s is the main server. */
static int open_error_log(server_rec *s, int is_main, apr_pool_t *p)
{
    const char *fname;
    int rc;

    if (*s->error_fname == '|') {
        apr_file_t *dummy = NULL;

        /* Spawn a new child logger.  If this is the main server_rec,
         * the new child must use a dummy stderr since the current
         * stderr might be a pipe to the old logger.  Otherwise, the
         * child inherits the parents stderr. */
        rc = log_child(p, s->error_fname + 1, &dummy, is_main);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "Couldn't start ErrorLog process");
            return DONE;
        }

