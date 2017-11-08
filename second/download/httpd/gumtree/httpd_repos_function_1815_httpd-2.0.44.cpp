static int piped_log_spawn(piped_log *pl)
{
    int rc;
    apr_procattr_t *procattr;
    apr_proc_t *procnew = NULL;
    apr_status_t status;

    if (((status = apr_procattr_create(&procattr, pl->p)) != APR_SUCCESS) ||
        ((status = apr_procattr_child_in_set(procattr,
                                             ap_piped_log_read_fd(pl),
                                             ap_piped_log_write_fd(pl)))
        != APR_SUCCESS)) {
        char buf[120];
        /* Something bad happened, give up and go away. */
        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
                     "piped_log_spawn: unable to setup child process '%s': %s",
                     pl->program, apr_strerror(status, buf, sizeof(buf)));
        rc = -1;
    }
    else {
        char **args;
        const char *pname;

        apr_tokenize_to_argv(pl->program, &args, pl->p);
        pname = apr_pstrdup(pl->p, args[0]);
        procnew = apr_pcalloc(pl->p, sizeof(apr_proc_t));
        rc = apr_proc_create(procnew, pname, (const char * const *) args,
                             NULL, procattr, pl->p);

        if (rc == APR_SUCCESS) {
            /* pjr - This no longer happens inside the child, */
            /*   I am assuming that if apr_proc_create was  */
            /*   successful that the child is running.        */
            RAISE_SIGSTOP(PIPED_LOG_SPAWN);
            pl->pid = procnew;
            ap_piped_log_write_fd(pl) = procnew->in;
            apr_proc_other_child_register(procnew, piped_log_maintenance, pl,
                                          ap_piped_log_write_fd(pl), pl->p);
        }
    }

    return 0;
}