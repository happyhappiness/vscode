static apr_status_t xml2enc_charset(request_rec* r, xmlCharEncoding* encp,
                                    const char** encoding)
{
    xml2ctx* ctx = ap_get_module_config(r->request_config, &xml2enc_module);
    if (!ctx || !(ctx->flags & ENC_INITIALISED)) {
        return APR_EAGAIN;
    }
    *encp = ctx->xml2enc;
    *encoding = ctx->encoding;
    return HAVE_ENCODING(ctx->xml2enc) ? APR_SUCCESS : APR_EGENERAL;
}