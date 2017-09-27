     * 1                 : The CMD_AJP13_SEND_BODY_CHUNK indicator byte (0x03).
     * 1                 : The last byte of this message always seems to be
     *                     0x00 and is not part of the chunk.
     */
    expected_len = msg->len - (AJP_HEADER_LEN + AJP_HEADER_SZ_LEN + 1 + 1);
    if (*len != expected_len) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
               "ajp_parse_data: Wrong chunk length. Length of chunk is %i,"
               " expected length is %i.", *len, expected_len);
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
