 * @return          APR_SUCCESS or error
 */
apr_status_t ajp_msg_create(apr_pool_t *pool, apr_size_t size, ajp_msg_t **rmsg)
{
    ajp_msg_t *msg = (ajp_msg_t *)apr_pcalloc(pool, sizeof(ajp_msg_t));

    msg->server_side = 0;

    msg->buf = (apr_byte_t *)apr_palloc(pool, size);
    msg->len = 0;
    msg->header_len = AJP_HEADER_LEN;
    msg->max_size = size;
    *rmsg = msg;

    return APR_SUCCESS;
