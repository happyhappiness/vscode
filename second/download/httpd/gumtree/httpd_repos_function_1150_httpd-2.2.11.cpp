static void *config_perdir_create(apr_pool_t *p, char *path)
{
    rewrite_perdir_conf *a;

    a = (rewrite_perdir_conf *)apr_pcalloc(p, sizeof(rewrite_perdir_conf));

    a->state           = ENGINE_DISABLED;
    a->options         = OPTION_NONE;
    a->baseurl         = NULL;
    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));

    if (path == NULL) {
        a->directory = NULL;
    }
    else {
        /* make sure it has a trailing slash */
        if (path[strlen(path)-1] == '/') {
            a->directory = apr_pstrdup(p, path);
        }
        else {
            a->directory = apr_pstrcat(p, path, "/", NULL);
        }
    }

    return (void *)a;
}