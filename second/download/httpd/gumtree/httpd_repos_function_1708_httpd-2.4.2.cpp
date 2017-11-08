static
apr_status_t ap_proxygetline(apr_bucket_brigade *bb, char *s, int n, request_rec *r,
                             int fold, int *writen)
{
    char *tmp_s = s;
    apr_status_t rv;
    apr_size_t len;

    rv = ap_rgetline(&tmp_s, n, &len, r, fold, bb);
    apr_brigade_cleanup(bb);

    if (rv == APR_SUCCESS) {
        *writen = (int) len;
    } else if (APR_STATUS_IS_ENOSPC(rv)) {
        *writen = n;
    } else {
        *writen = -1;
    }

    return rv;
}