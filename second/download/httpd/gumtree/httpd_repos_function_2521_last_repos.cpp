static int has_relation(link_ctx *ctx, const char *rel)
{
    const char *s, *val = apr_table_get(ctx->params, "rel");
    if (val) {
        if (!strcmp(rel, val)) {
            return 1;
        }
        s = ap_strstr_c(val, rel);
        if (s && (s == val || s[-1] == ' ')) {
            s += strlen(rel);
            if (!*s || *s == ' ') {
                return 1;
            }
        }
    }
    return 0;
}