static void logio_insert_filter(request_rec * r)
{
    logio_dirconf_t *conf = ap_get_module_config(r->per_dir_config,
                                                 &logio_module);
    if (conf->track_ttfb) { 
        ap_add_output_filter(logio_ttfb_filter_name, NULL, r, r->connection);
    }
    return;
}