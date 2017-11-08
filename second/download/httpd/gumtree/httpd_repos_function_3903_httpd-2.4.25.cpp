static int op_nz(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    const char *name = (const char *)data;
    if (name[0] == 'z')
        return (arg[0] == '\0');
    else
        return (arg[0] != '\0');
}