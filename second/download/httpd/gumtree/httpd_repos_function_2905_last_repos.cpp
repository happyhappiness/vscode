void h2_ctx_clear(const conn_rec *c)
{
    ap_assert(c);
    ap_set_module_config(c->conn_config, &http2_module, NULL);
}