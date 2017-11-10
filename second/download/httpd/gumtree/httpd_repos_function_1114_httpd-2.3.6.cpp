static int socache_mc_id2key(ap_socache_instance_t *ctx,
                             const unsigned char *id, unsigned int idlen,
                             char *key, apr_size_t keylen)
{
    char *cp;
    unsigned int n;

    if (idlen * 2 + ctx->taglen >= keylen)
        return 1;

    cp = apr_cpystrn(key, ctx->tag, ctx->taglen);

    for (n = 0; n < idlen; n++) {
        apr_snprintf(cp, 3, "%02X", (unsigned) id[n]);
        cp += 2;
    }

    *cp = '\0';
    return 0;
}