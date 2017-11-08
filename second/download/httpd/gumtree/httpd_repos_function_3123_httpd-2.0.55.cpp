apr_status_t apr_sendfile(apr_socket_t *sock, apr_file_t *file,
                          apr_hdtr_t *hdtr, apr_off_t *offset, apr_size_t *len,
                          apr_int32_t flags)
{
    return apr_socket_sendfile(sock, file, hdtr, offset, len, flags);
}