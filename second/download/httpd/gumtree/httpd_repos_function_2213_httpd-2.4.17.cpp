static int count_header(void *ctx, const char *key, const char *value)
{
    if (!ignore_header(key)) {
        nvctx_t *nvctx = (nvctx_t*)ctx;
        nvctx->nvlen++;
        nvctx->nvstrlen += strlen(key) + strlen(value) + 2;
    }
    return 1;
}