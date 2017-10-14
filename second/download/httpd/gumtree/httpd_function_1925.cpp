apr_status_t ajp_msg_check_header(ajp_msg_t *msg, apr_size_t *len)
{
    apr_byte_t *head = msg->buf;
    apr_size_t msglen;

    if (!((head[0] == 0x41 && head[1] == 0x42) ||
          (head[0] == 0x12 && head[1] == 0x34))) {

        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                      "ajp_check_msg_header() got bad signature %x%x",
                      head[0], head[1]);

        return AJP_EBAD_SIGNATURE;
    }

    msglen  = ((head[2] & 0xff) << 8);
    msglen += (head[3] & 0xFF);

    if (msglen > msg->max_size) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "ajp_check_msg_header() incoming message is "
                     "too big %" APR_SIZE_T_FMT ", max is %" APR_SIZE_T_FMT,
                     msglen, msg->max_size);
        return AJP_ETOBIG;
    }

    msg->len = msglen + AJP_HEADER_LEN;
    msg->pos = AJP_HEADER_LEN;
    *len     = msglen;

    return APR_SUCCESS;
}