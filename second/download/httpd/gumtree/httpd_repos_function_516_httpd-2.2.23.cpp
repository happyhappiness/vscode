static const char *set_metafiles(cmd_parms *parms, void *in_dconf, int arg)
{
    cern_meta_dir_config *dconf = in_dconf;

    dconf->metafiles = arg;
    return NULL;
}