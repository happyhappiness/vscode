static apr_status_t dbd_destroy(void *data)
{
    dbd_group_t *group = data;

    group->destroyed = 1;

    return APR_SUCCESS;
}