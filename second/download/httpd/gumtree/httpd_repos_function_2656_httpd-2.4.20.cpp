void h2_ctx_clear(const conn_rec *c)
{
    AP_DEBUG_ASSERT(c);
    ap_set_module_config(c->conn_config, &http2_module, NULL);
}