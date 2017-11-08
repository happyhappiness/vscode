static void xml2enc_hooks(apr_pool_t* pool)
{
    ap_register_output_filter_protocol("xml2enc", xml2enc_ffunc,
                                       xml2enc_filter_init,
                                       AP_FTYPE_RESOURCE, PROTO_FLAGS);
    APR_REGISTER_OPTIONAL_FN(xml2enc_filter);
    APR_REGISTER_OPTIONAL_FN(xml2enc_charset);
    seek_meta_ctype = ap_pregcomp(pool,
                       "(<meta[^>]*http-equiv[ \t\r\n='\"]*content-type[^>]*>)",
                                  AP_REG_EXTENDED|AP_REG_ICASE) ;
    seek_charset = ap_pregcomp(pool, "charset=([A-Za-z0-9_-]+)",
                               AP_REG_EXTENDED|AP_REG_ICASE) ;
}