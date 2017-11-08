static void *create_cern_meta_dir_config(apr_pool_t *p, char *dummy)
{
    cern_meta_dir_config *new =
    (cern_meta_dir_config *) apr_palloc(p, sizeof(cern_meta_dir_config));

    new->metadir = NULL;
    new->metasuffix = NULL;
    new->metafiles = DEFAULT_METAFILES;

    return new;
}