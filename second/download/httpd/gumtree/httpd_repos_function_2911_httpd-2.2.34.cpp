static apr_status_t dbd_free_snapshot(void *snap)
{
    switch (OCIDescriptorFree(snap, OCI_DTYPE_SNAP)) {
    case OCI_SUCCESS:
        return APR_SUCCESS;
    default:
        return APR_EGENERAL;
    }
}