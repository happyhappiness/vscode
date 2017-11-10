static void *create_dbm_auth_dir_config(apr_pool_t *p, char *d)
{
    dbm_auth_config_rec *conf = apr_palloc(p, sizeof(*conf));

    conf->auth_dbmpwfile = NULL;
    conf->auth_dbmgrpfile = NULL;
    conf->auth_dbmtype = "default";
    conf->auth_dbmauthoritative = 1;  /* fortress is secure by default */

    return conf;
}