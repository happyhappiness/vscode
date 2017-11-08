static int add_header(void *ctx, const char *key, const char *value)
{
    if (!ignore_header(key)) {
        nvctx_t *nvctx = (nvctx_t*)ctx;
        NV_ADD_CS_CS(nvctx, key, value);
    }
    return 1;
}