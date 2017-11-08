static apr_status_t ap_expr_term(void *expr)
{
    if (isvar) {
        ap_regfree(isvar);
        isvar = NULL;
    }
    return APR_SUCCESS;
}