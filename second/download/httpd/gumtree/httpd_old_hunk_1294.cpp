        procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
        status = apr_proc_create(procnew, pname, (const char * const *) args,
                                 NULL, procattr, pl->p);

        if (status == APR_SUCCESS) {
            pl->pid = procnew;
            ap_piped_log_write_fd(pl) = procnew->in;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          ap_piped_log_write_fd(pl), pl->p);
        }
        else {
            char buf[120];
            /* Something bad happened, give up and go away. */
            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                         "unable to start piped log program '%s': %s",
                         pl->program, apr_strerror(status, buf, sizeof(buf)));
            rc = -1;
        }
    }

    return rc;
}


static void piped_log_maintenance(int reason, void *data, apr_wait_t status)
{
    piped_log *pl = data;
