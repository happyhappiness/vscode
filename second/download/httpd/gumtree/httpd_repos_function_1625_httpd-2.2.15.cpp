static void *merge_ef_dir_conf(apr_pool_t *p, void *basev, void *overridesv)
{
    ef_dir_t *a = (ef_dir_t *)apr_pcalloc (p, sizeof(ef_dir_t));
    ef_dir_t *base = (ef_dir_t *)basev, *over = (ef_dir_t *)overridesv;

    if (over->debug != -1) {        /* if admin coded something... */
        a->debug = over->debug;
    }
    else {
        a->debug = base->debug;
    }

    if (over->log_stderr != -1) {   /* if admin coded something... */
        a->log_stderr = over->log_stderr;
    }
    else {
        a->log_stderr = base->log_stderr;
    }

    if (over->onfail != -1) {   /* if admin coded something... */
        a->onfail = over->onfail;
    }
    else {
        a->onfail = base->onfail;
    }

    return a;
}