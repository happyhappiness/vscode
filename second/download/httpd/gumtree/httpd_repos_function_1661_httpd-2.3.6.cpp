static int serf_handler(request_rec *r)
{
    serf_config_t *conf = ap_get_module_config(r->per_dir_config,
                                               &serf_module);

    if (conf->on == 0) {
        return DECLINED;
    }

    return drive_serf(r, conf);
}