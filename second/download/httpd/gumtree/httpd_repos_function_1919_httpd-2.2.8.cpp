static const char *get_userpw_hash(const request_rec *r,
                                   const digest_header_rec *resp,
                                   const digest_config_rec *conf)
{
    return ap_md5(r->pool,
             (unsigned char *) apr_pstrcat(r->pool, conf->ha1, ":", resp->nonce,
                                           ":", resp->cnonce, NULL));
}