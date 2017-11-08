static apr_status_t arr_elts_getstr(void *buf, apr_size_t bufsiz, void *param)
{
    arr_elts_param_t *arr_param = (arr_elts_param_t *)param;
    char *elt;

    /* End of array reached? */
    if (++arr_param->curr_idx > arr_param->array->nelts)
        return APR_EOF;

    /* return the line */
    elt = ((char **)arr_param->array->elts)[arr_param->curr_idx - 1];
    if (apr_cpystrn(buf, elt, bufsiz) - (char *)buf >= bufsiz - 1)
        return APR_ENOSPC;
    return APR_SUCCESS;
}