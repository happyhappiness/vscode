static int arr_elts_close(void *param)
{
    arr_elts_param_t *arr_param = (arr_elts_param_t *)param;

    arr_param->curr_idx = arr_param->array->nelts;

    return 0;
}