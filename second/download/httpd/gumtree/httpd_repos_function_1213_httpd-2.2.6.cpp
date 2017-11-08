static ap_unix_identity_t *get_suexec_id_doer(const request_rec *r)
{
    suexec_config_t *cfg =
    (suexec_config_t *) ap_get_module_config(r->per_dir_config, &suexec_module);

    return cfg->active ? &cfg->ugid : NULL;
}