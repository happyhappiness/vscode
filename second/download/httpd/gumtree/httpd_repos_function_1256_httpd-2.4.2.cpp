static apr_status_t dbd_release(void *data)
{
    dbd_acquire_t *acq = data;
    apr_reslist_release(acq->reslist, acq->rec);
    return APR_SUCCESS;
}