            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
            (*fpin) = procnew->in;
            /* read handle to pipe not kept open, so no need to call
             * close_handle_in_child()
             */
        }
    }

    return rc;
}

static int open_error_log(server_rec *s, apr_pool_t *p)
{
    const char *fname;
    int rc;

    if (*s->error_fname == '|') {
        apr_file_t *dummy = NULL;

        /* This starts a new process... */
        rc = log_child (p, s->error_fname + 1, &dummy);
        if (rc != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_STARTUP, rc, NULL,
                         "Couldn't start ErrorLog process");
            return DONE;
        }

