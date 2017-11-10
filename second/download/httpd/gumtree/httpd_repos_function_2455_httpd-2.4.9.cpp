static apr_status_t slotmem_put(ap_slotmem_instance_t *slot, unsigned int id, unsigned char *src, apr_size_t src_len)
{
    void *ptr;
    char *inuse;
    apr_status_t ret;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse + id;
    if (id >= slot->num) {
        return APR_EINVAL;
    }
    if (AP_SLOTMEM_IS_PREGRAB(slot) && !*inuse) {
        return APR_NOTFOUND;
    }
    ret = slotmem_dptr(slot, id, &ptr);
    if (ret != APR_SUCCESS) {
        return ret;
    }
    *inuse=1;
    memcpy(ptr, src, src_len); /* bounds check? */
    return APR_SUCCESS;
}