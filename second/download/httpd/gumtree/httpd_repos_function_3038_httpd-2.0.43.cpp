static void collapse_iovec(char **buf, int *len, struct iovec *iovec, int numvec, apr_pool_t *p)
{
    int ptr = 0;

    if (numvec == 1) {
        *buf = iovec[0].iov_base;
        *len = iovec[0].iov_len;
    }
    else {
        int i;
        for (i = 0; i < numvec; i++) {
            *len += iovec[i].iov_len;
        }

        *buf = apr_palloc(p, *len); /* Should this be a malloc? */

        for (i = 0; i < numvec; i++) {
            memcpy((char*)*buf + ptr, iovec[i].iov_base, iovec[i].iov_len);
            ptr += iovec[i].iov_len;
        }
    }
}