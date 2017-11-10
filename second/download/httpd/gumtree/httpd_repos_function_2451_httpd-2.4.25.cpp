static int set_push_header(void *ctx, const char *key, const char *value) 
{
    size_t klen = strlen(key);
    if (H2_HD_MATCH_LIT("User-Agent", key, klen)
        || H2_HD_MATCH_LIT("Accept", key, klen)
        || H2_HD_MATCH_LIT("Accept-Encoding", key, klen)
        || H2_HD_MATCH_LIT("Accept-Language", key, klen)
        || H2_HD_MATCH_LIT("Cache-Control", key, klen)) {
        apr_table_setn(ctx, key, value);
    }
    return 1;
}