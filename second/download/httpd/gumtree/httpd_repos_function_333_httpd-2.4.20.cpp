static void *dav_create_dir_config(apr_pool_t *p, char *dir)
{
    /* NOTE: dir==NULL creates the default per-dir config */

    dav_dir_conf *conf;

    conf = (dav_dir_conf *)apr_pcalloc(p, sizeof(*conf));

    /* clean up the directory to remove any trailing slash */
    if (dir != NULL) {
        char *d;
        apr_size_t l;

        l = strlen(dir);
        d = apr_pstrmemdup(p, dir, l);
        if (l > 1 && d[l - 1] == '/')
            d[l - 1] = '\0';
        conf->dir = d;
    }

    return conf;
}