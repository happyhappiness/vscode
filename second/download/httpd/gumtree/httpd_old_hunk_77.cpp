                                         REWRITELOCK_MODE)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, s,
                     "mod_rewrite: Parent could not create RewriteLock "
                     "file %s", conf->rewritelockfile);
        exit(1);
    }
    return;
}

static void rewritelock_open(server_rec *s, pool *p)
{
    rewrite_server_conf *conf;

    conf = ap_get_module_config(s->module_config, &rewrite_module);

    /* only operate if a lockfile is used */
    if (conf->rewritelockfile == NULL
        || *(conf->rewritelockfile) == '\0')
        return;

    /* open the lockfile (once per child) to get a unique fd */
    if ((conf->rewritelockfp = ap_popenf(p, conf->rewritelockfile,
                                         O_WRONLY,
                                         REWRITELOCK_MODE)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, s,
