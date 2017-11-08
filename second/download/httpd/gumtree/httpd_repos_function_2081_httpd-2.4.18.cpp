apr_status_t  ajp_send_data_msg(apr_socket_t *sock,
                                ajp_msg_t *msg, apr_size_t len)
{

    msg->buf[4] = (apr_byte_t)((len >> 8) & 0xFF);
    msg->buf[5] = (apr_byte_t)(len & 0xFF);

    msg->len += len + 2; /* + 1 XXXX where is '\0' */

    return ajp_ilink_send(sock, msg);

}