static void *arr_elts_getstr(void *buf, size_t bufsiz, void *param)
{
    arr_elts_param_t *arr_param = (arr_elts_param_t *)param;

    /* End of array reached? */
    if (++arr_param->curr_idx > arr_param->array->nelts)
        return NULL;

    /* return the line */
    apr_cpystrn(buf,
                ((char **)arr_param->array->elts)[arr_param->curr_idx - 1],
                bufsiz);

    return buf;
}