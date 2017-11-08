static apr_status_t collapse_iovec(char **off, apr_size_t *len, 
                                   struct iovec *iovec, int numvec, 
                                   char *buf, apr_size_t buflen)
{
    if (numvec == 1) {
        *off = iovec[0].iov_base;
        *len = iovec[0].iov_len;
    }
    else {
        int i;
        for (i = 0; i < numvec; i++) {
            *len += iovec[i].iov_len;
        }

        if (*len > buflen) {
            *len = 0;
            return APR_INCOMPLETE;
        }

        *off = buf;

        for (i = 0; i < numvec; i++) {
            memcpy(buf, iovec[i].iov_base, iovec[i].iov_len);
            buf += iovec[i].iov_len;
        }
    }
    return APR_SUCCESS;
}