        return AJP_EBAD_HEADER;
    }
    *ptr = (char *)&(msg->buf[msg->pos]);
    return APR_SUCCESS;
}

/*
 * Allocate a msg to send data
 */
apr_status_t  ajp_alloc_data_msg(apr_pool_t *pool, char **ptr, apr_size_t *len,
                                 ajp_msg_t **msg)
{
