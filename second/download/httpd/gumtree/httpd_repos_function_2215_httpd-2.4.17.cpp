static void addnv_lit_cs(nvctx_t *ctx, const char *key, size_t key_len,
                         const char *value, size_t val_len)
{
    nghttp2_nv *nv = &ctx->nv[ctx->offset];
    
    NV_BUF_ADD(ctx, value, val_len);
    
    nv->name = (uint8_t*)key;
    nv->namelen = key_len;
    nv->value = (uint8_t*)value;
    nv->valuelen = val_len;
    
    ctx->offset++;
}