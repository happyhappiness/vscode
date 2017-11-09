static apr_status_t xml2enc_filter_init(ap_filter_t* f)
{
    xml2ctx* ctx;
    if (!f->ctx) {
        xml2cfg* cfg = ap_get_module_config(f->r->per_dir_config,
                                            &xml2enc_module);
        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(xml2ctx));
        ctx->xml2enc = XML_CHAR_ENCODING_NONE;
        if (cfg->skipto != NULL) {
            ctx->flags |= ENC_SKIPTO;
        }
    }
    return APR_SUCCESS;
}