static apr_status_t sock_writev(int fd, request_rec *r, int count, ...)
{
    va_list ap;
    int rc;
    struct iovec *vec;
    int i;
    int total_bytes = 0;

    vec = (struct iovec *)apr_palloc(r->pool, count * sizeof(struct iovec));
    va_start(ap, count);
    for (i = 0; i < count; i++) {
        vec[i].iov_base = va_arg(ap, caddr_t);
        vec[i].iov_len  = va_arg(ap, apr_size_t);
        total_bytes += vec[i].iov_len;
    }
    va_end(ap);

    do {
        rc = writev(fd, vec, count);
    } while (rc < 0 && errno == EINTR);
    if (rc < 0) {
        return errno;
    }

    return APR_SUCCESS;
}