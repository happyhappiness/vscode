static int inc_rec(ap_expr_eval_ctx_t *ctx)
{
    if (ctx->reclvl < AP_EXPR_MAX_RECURSION) {
        ctx->reclvl++;
        return 0;
    }
    *ctx->err = "Recursion limit reached";
    /* short circuit further evaluation */
    ctx->reclvl = INT_MAX;
    return 1;
}