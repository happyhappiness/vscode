static apr_status_t ilink_read(apr_socket_t *sock, apr_byte_t *buf,
                               apr_size_t len)
{
    apr_size_t   length = len;
    apr_size_t   rdlen  = 0;
    apr_status_t status;

    while (rdlen < len) {

        status = apr_socket_recv(sock, (char *)(buf + rdlen), &length);

        if (status == APR_EOF)
            return status;          /* socket closed. */
        else if (APR_STATUS_IS_EAGAIN(status))
            continue;
        else if (status != APR_SUCCESS)
            return status;          /* any error. */

        rdlen += length;
        length = len - rdlen;
    }
    return APR_SUCCESS;
}