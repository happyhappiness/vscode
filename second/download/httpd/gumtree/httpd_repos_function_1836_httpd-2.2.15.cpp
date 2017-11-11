static x_cfg *our_dconfig(const request_rec *r)
{
    return (x_cfg *) ap_get_module_config(r->per_dir_config, &example_module);
}