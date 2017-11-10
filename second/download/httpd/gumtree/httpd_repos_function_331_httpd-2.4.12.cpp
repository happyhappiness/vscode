static void *dav_create_server_config(apr_pool_t *p, server_rec *s)
{
    dav_server_conf *newconf;

    newconf = (dav_server_conf *)apr_pcalloc(p, sizeof(*newconf));

    /* ### this isn't used at the moment... */

    return newconf;
}