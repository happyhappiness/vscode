static void do_expand_env(data_item *env, rewrite_ctx *ctx)
{
    char *name, *val;

    while (env) {
        name = do_expand(env->data, ctx, NULL);
        if (*name == '!') {
            name++;
            apr_table_unset(ctx->r->subprocess_env, name);
            rewritelog((ctx->r, 5, NULL, "unsetting env variable '%s'", name));
        }
        else {
            if ((val = ap_strchr(name, ':')) != NULL) {
                *val++ = '\0';
            } else {
                val = "";
            }

            apr_table_set(ctx->r->subprocess_env, name, val);
            rewritelog((ctx->r, 5, NULL, "setting env variable '%s' to '%s'",
                        name, val));
        }

        env = env->next;
    }

    return;
}