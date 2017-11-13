static apr_status_t run_rewritemap_programs(server_rec *s, apr_pool_t *p)
{
    rewrite_server_conf *conf;
    apr_array_header_t *rewritemaps;
    rewritemap_entry *entries;
    int i;
    apr_status_t rc;

    conf = ap_get_module_config(s->module_config, &rewrite_module);

    /*  If the engine isn't turned on,
     *  don't even try to do anything.
     */
    if (conf->state == ENGINE_DISABLED) {
        return APR_SUCCESS;
    }

    rewritemaps = conf->rewritemaps;
    entries = (rewritemap_entry *)rewritemaps->elts;
    for (i = 0; i < rewritemaps->nelts; i++) {
        apr_file_t *fpin = NULL;
        apr_file_t *fpout = NULL;
        rewritemap_entry *map = &entries[i];

        if (map->type != MAPTYPE_PRG) {
            continue;
        }
        if (map->argv[0] == NULL
            || *(map->argv[0]) == '\0'
            || map->fpin  != NULL
            || map->fpout != NULL        ) {
            continue;
        }
        rc = rewritemap_program_child(p, map->argv[0], map->argv,
                                      &fpout, &fpin);
        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not startup RewriteMap "
                         "program %s", map->datafile);
            return rc;
        }
        map->fpin  = fpin;
        map->fpout = fpout;
    }
    return APR_SUCCESS;
}