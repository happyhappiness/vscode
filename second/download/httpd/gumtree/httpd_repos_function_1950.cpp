static apr_status_t sed_eval_cleanup(void *data)
{
    sed_eval_t *eval = (sed_eval_t *) data;
    sed_destroy_eval(eval);
    return APR_SUCCESS;
}