    conf = ap_get_module_config(s->module_config, &rewrite_module);

    /*  If the engine isn't turned on,
     *  don't even try to do anything.
     */
    if (conf->state == ENGINE_DISABLED) {
        return;
    }

    rewritemaps = conf->rewritemaps;
    entries = (rewritemap_entry *)rewritemaps->elts;
    for (i = 0; i < rewritemaps->nelts; i++) {
        map = &entries[i];
        if (map->type != MAPTYPE_PRG) {
            continue;
        }
        if (map->datafile == NULL
            || *(map->datafile) == '\0'
            || map->fpin  != NULL
            || map->fpout != NULL        ) {
            continue;
        }
        fpin  = NULL;
        fpout = NULL;
        rc = rewritemap_program_child(p, map->datafile,
                                     &fpout, &fpin, &fperr);
        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not fork child for "
                         "RewriteMap process");
            exit(1);
        }
        map->fpin  = fpin;
        map->fpout = fpout;
        map->fperr = fperr;
    }
    return;
}

/* child process code */
static apr_status_t rewritemap_program_child(apr_pool_t *p, const char *progname,
                                             apr_file_t **fpout, apr_file_t **fpin,
                                             apr_file_t **fperr)
{
    apr_status_t rc;
    apr_procattr_t *procattr;
    apr_proc_t *procnew;

    if (((rc = apr_procattr_create(&procattr, p)) != APR_SUCCESS) ||
        ((rc = apr_procattr_io_set(procattr, APR_FULL_BLOCK,
                                  APR_FULL_NONBLOCK,
                                  APR_FULL_NONBLOCK)) != APR_SUCCESS) ||
        ((rc = apr_procattr_dir_set(procattr, 
                                   ap_make_dirstr_parent(p, progname)))
         != APR_SUCCESS) ||
        ((rc = apr_procattr_cmdtype_set(procattr, APR_PROGRAM)) != APR_SUCCESS)) {
        /* Something bad happened, give up and go away. */
    }
    else {
        procnew = apr_pcalloc(p, sizeof(*procnew));
        rc = apr_proc_create(procnew, progname, NULL, NULL, procattr, p);
    
        if (rc == APR_SUCCESS) {
            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);

            if (fpin) {
                (*fpin) = procnew->in;
