apr_status_t ajp_msg_reset(ajp_msg_t *msg)
{
    msg->len = AJP_HEADER_LEN;
    msg->pos = AJP_HEADER_LEN;

    return APR_SUCCESS;
}