static apr_status_t sed_compile_errf(void *data, const char *error)
{
    sed_expr_config *sed_cfg = (sed_expr_config *) data;
    sed_cfg->last_error = error;
    return APR_SUCCESS;
}