static apr_status_t slotmem_dptr(ap_slotmem_instance_t *slot,
                                 unsigned int id, void **mem)
{
    void *ptr;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }
    if (id >= slot->desc.num) {
        return APR_ENOSHMAVAIL;
    }

    ptr = slot->base + slot->desc.size * id;
    if (!ptr) {
        return APR_ENOSHMAVAIL;
    }
    *mem = ptr;
    return APR_SUCCESS;
}