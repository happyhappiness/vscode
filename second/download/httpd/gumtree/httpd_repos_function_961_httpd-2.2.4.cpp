static apr_status_t store_array(apr_file_t *fd, apr_array_header_t* arr)
{
    int i;
    apr_status_t rv;
    struct iovec iov[2];
    apr_size_t amt;
    const char **elts;

    elts = (const char **) arr->elts;

    for (i = 0; i < arr->nelts; i++) {
        iov[0].iov_base = (char*) elts[i];
        iov[0].iov_len = strlen(elts[i]);
        iov[1].iov_base = CRLF;
        iov[1].iov_len = sizeof(CRLF) - 1;

        rv = apr_file_writev(fd, (const struct iovec *) &iov, 2,
                             &amt);
        if (rv != APR_SUCCESS) {
            return rv;
        }
    }

    iov[0].iov_base = CRLF;
    iov[0].iov_len = sizeof(CRLF) - 1;

    return apr_file_writev(fd, (const struct iovec *) &iov, 1,
                         &amt);
}