static const char *set_metadir(cmd_parms *parms, void *in_dconf, const char *arg)
{
    cern_meta_dir_config *dconf = in_dconf;

    dconf->metadir = arg;
    return NULL;
}