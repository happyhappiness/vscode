        return APR_SUCCESS;
    }

    rewritemaps = conf->rewritemaps;
    entries = (rewritemap_entry *)rewritemaps->elts;
    for (i = 0; i < rewritemaps->nelts; i++) {
        map = &entries[i];
        if (map->type != MAPTYPE_PRG) {
            continue;
        }
        if (map->argv[0] == NULL
            || *(map->argv[0]) == '\0'
            || map->fpin  != NULL
            || map->fpout != NULL        ) {
            continue;
        }
        fpin  = NULL;
        fpout = NULL;
        rc = rewritemap_program_child(p, map->argv[0], map->argv,
                                     &fpout, &fpin, &fperr);
        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not startup RewriteMap "
                         "program %s", map->datafile);
            return rc;
        }
        map->fpin  = fpin;
        map->fpout = fpout;
        map->fperr = fperr;
    }
    return APR_SUCCESS;
}

/* child process code */
static apr_status_t rewritemap_program_child(apr_pool_t *p, 
                                             const char *progname, char **argv,
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
                                   ap_make_dirstr_parent(p, argv[0])))
         != APR_SUCCESS) ||
        ((rc = apr_procattr_cmdtype_set(procattr, APR_PROGRAM)) != APR_SUCCESS)) {
        /* Something bad happened, give up and go away. */
    }
