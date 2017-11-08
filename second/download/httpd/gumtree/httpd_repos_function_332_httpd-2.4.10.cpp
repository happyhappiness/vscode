static void *dav_merge_server_config(apr_pool_t *p, void *base, void *overrides)
{
#if 0
    dav_server_conf *child = overrides;
#endif
    dav_server_conf *newconf;

    newconf = (dav_server_conf *)apr_pcalloc(p, sizeof(*newconf));

    /* ### nothing to merge right now... */

    return newconf;
}