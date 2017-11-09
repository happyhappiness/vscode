static int socache_mc_id2key(ap_socache_instance_t *ctx,
                             const unsigned char *id, unsigned int idlen,
                             char *key, apr_size_t keylen)
{
    char *cp;

    if (idlen * 2 + ctx->taglen >= keylen)
        return 1;

    cp = apr_cpystrn(key, ctx->tag, ctx->taglen);
    ap_bin2hex(id, idlen, cp);

    return 0;
}