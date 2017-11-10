static const char *misc_var_fn(ap_expr_eval_ctx_t *ctx, const void *data)
{
    apr_time_exp_t tm;
    int index = ((const char **)data - misc_var_names);
    apr_time_exp_lt(&tm, apr_time_now());

    switch (index) {
    case 0:
        return apr_psprintf(ctx->p, "%02d%02d", (tm.tm_year / 100) + 19,
                            tm.tm_year % 100);
    case 1:
        return apr_psprintf(ctx->p, "%02d", tm.tm_mon+1);
    case 2:
        return apr_psprintf(ctx->p, "%02d", tm.tm_mday);
    case 3:
        return apr_psprintf(ctx->p, "%02d", tm.tm_hour);
    case 4:
        return apr_psprintf(ctx->p, "%02d", tm.tm_min);
    case 5:
        return apr_psprintf(ctx->p, "%02d", tm.tm_sec);
    case 6:
        return apr_psprintf(ctx->p, "%d", tm.tm_wday);
    case 7:
        return apr_psprintf(ctx->p, "%02d%02d%02d%02d%02d%02d%02d",
                            (tm.tm_year / 100) + 19, (tm.tm_year % 100),
                            tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min,
                            tm.tm_sec);
    case 8:
        return ap_get_server_banner();
    case 9:
        return apr_itoa(ctx->p, MODULE_MAGIC_NUMBER);
    default:
        ap_assert(0);
    }

    return NULL;
}