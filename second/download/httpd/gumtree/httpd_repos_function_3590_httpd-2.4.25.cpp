static int authz_core_check_config(apr_pool_t *p, apr_pool_t *plog,
                                   apr_pool_t *ptemp, server_rec *s)
{
    authz_core_dir_conf *conf = authz_core_first_dir_conf;

    while (conf) {
        if (conf->section) {
            if (authz_core_check_section(p, s, conf->section, 1) != OK) {
                return !OK;
            }
        }

        conf = conf->next;
    }

    return OK;
}