        }
    }

    return rc;
}

static void open_error_log(server_rec *s, apr_pool_t *p)
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
            exit(1);
        }

        s->error_log = dummy;
    }

#ifdef HAVE_SYSLOG
