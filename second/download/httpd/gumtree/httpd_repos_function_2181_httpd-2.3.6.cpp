static x_cfg *our_cconfig(const conn_rec *c)
{
    return (x_cfg *) ap_get_module_config(c->conn_config, &example_hooks_module);
}