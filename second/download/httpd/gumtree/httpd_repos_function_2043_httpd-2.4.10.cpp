apr_status_t  ajp_alloc_data_msg(apr_pool_t *pool, char **ptr, apr_size_t *len,
                                 ajp_msg_t **msg)
{
    apr_status_t rc;

    if ((rc = ajp_msg_create(pool, *len, msg)) != APR_SUCCESS)
        return rc;
    ajp_msg_reset(*msg);
    *ptr = (char *)&((*msg)->buf[6]);
    *len =  *len - 6;

    return APR_SUCCESS;
}