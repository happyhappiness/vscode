

/**
 * Create an AJP Message from pool
 *
 * @param pool      memory pool to allocate AJP message from
 * @param rmsg      Pointer to newly created AJP message
 * @return          APR_SUCCESS or error
 */
apr_status_t ajp_msg_create(apr_pool_t *pool, ajp_msg_t **rmsg)
{
    ajp_msg_t *msg = (ajp_msg_t *)apr_pcalloc(pool, sizeof(ajp_msg_t));

    if (!msg) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_msg_create(): can't allocate AJP message memory");
        return APR_ENOPOOL;
    }

    msg->server_side = 0;

    msg->buf = (apr_byte_t *)apr_palloc(pool, AJP_MSG_BUFFER_SZ);

    /* XXX: This should never happen
     * In case if the OS cannont allocate 8K of data
     * we are in serious trouble
     * No need to check the alloc return value, cause the
     * core dump is probably the best solution anyhow.
