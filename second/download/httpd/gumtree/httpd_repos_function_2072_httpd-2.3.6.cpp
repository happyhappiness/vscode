static const char *ssi_parse_string(request_rec *r, const char *in)
{
    include_ctx_t *ctx = ap_get_module_config(r->request_config,
                                              &include_module);
    return ap_ssi_parse_string(ctx, in, NULL, 0, SSI_EXPAND_DROP_NAME);
}