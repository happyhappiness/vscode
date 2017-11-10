static void gen_nonce_hash(char *hash, const char *timestr, const char *opaque,
                           const server_rec *server,
                           const digest_config_rec *conf)
{
    const char *hex = "0123456789abcdef";
    unsigned char sha1[APR_SHA1_DIGESTSIZE];
    apr_sha1_ctx_t ctx;
    int idx;

    memcpy(&ctx, &conf->nonce_ctx, sizeof(ctx));
    /*
    apr_sha1_update_binary(&ctx, (const unsigned char *) server->server_hostname,
                         strlen(server->server_hostname));
    apr_sha1_update_binary(&ctx, (const unsigned char *) &server->port,
                         sizeof(server->port));
     */
    apr_sha1_update_binary(&ctx, (const unsigned char *) timestr, strlen(timestr));
    if (opaque) {
        apr_sha1_update_binary(&ctx, (const unsigned char *) opaque,
                             strlen(opaque));
    }
    apr_sha1_final(sha1, &ctx);

    for (idx=0; idx<APR_SHA1_DIGESTSIZE; idx++) {
        *hash++ = hex[sha1[idx] >> 4];
        *hash++ = hex[sha1[idx] & 0xF];
    }

    *hash++ = '\0';
}