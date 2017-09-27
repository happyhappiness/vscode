{
    logio_dirconf_t *conf = ap_get_module_config(r->per_dir_config,
                                                 &logio_module);
    if (conf->track_ttfb) { 
        ap_add_output_filter(logio_ttfb_filter_name, NULL, r, r->connection);
    }
    return;
}

static const char *logio_track_ttfb(cmd_parms *cmd, void *in_dir_config, int arg)
{
    logio_dirconf_t *dir_config = in_dir_config;
    dir_config->track_ttfb = arg;
