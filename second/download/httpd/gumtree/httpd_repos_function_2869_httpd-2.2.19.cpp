static apr_status_t dbd_free_lobdesc(void *lob)
{
    switch (OCIDescriptorFree(lob, OCI_DTYPE_LOB)) {
    case OCI_SUCCESS:
        return APR_SUCCESS;
    default:
        return APR_EGENERAL;
    }
}