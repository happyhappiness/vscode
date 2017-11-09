static apr_status_t ssl_stapling_certid_free(void *data)
{
    OCSP_CERTID *cid = data;

    if (cid) {
        OCSP_CERTID_free(cid);
    }

    return APR_SUCCESS;
}