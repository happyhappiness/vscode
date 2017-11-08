static int set_h1_header(void *ctx, const char *key, const char *value)
{
    h1_ctx *x = ctx;
    size_t klen = strlen(key);
    if (!h2_req_ignore_header(key, klen)) {
        add_h1_header(x->req, x->pool, key, klen, value, strlen(value));
    }
    return 1;
}