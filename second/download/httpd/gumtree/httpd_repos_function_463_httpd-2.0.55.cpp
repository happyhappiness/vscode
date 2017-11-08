static void *merge_cern_meta_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    cern_meta_dir_config *base = (cern_meta_dir_config *) basev;
    cern_meta_dir_config *add = (cern_meta_dir_config *) addv;
    cern_meta_dir_config *new =
    (cern_meta_dir_config *) apr_palloc(p, sizeof(cern_meta_dir_config));

    new->metadir = add->metadir ? add->metadir : base->metadir;
    new->metasuffix = add->metasuffix ? add->metasuffix : base->metasuffix;
    new->metafiles = add->metafiles;

    return new;
}