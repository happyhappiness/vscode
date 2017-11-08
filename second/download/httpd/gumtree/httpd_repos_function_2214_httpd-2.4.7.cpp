static void *create_ef_dir_conf(apr_pool_t *p, char *dummy)
{
    ef_dir_t *dc = (ef_dir_t *)apr_pcalloc(p, sizeof(ef_dir_t));

    dc->log_stderr = -1;
    dc->onfail = -1;

    return dc;
}