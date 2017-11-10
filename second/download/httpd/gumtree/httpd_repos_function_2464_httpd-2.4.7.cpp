static apr_status_t slotmem_release(ap_slotmem_instance_t *slot, unsigned int id)
{
    char *inuse;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse;

    if (id >= slot->num) {
        return APR_EINVAL;
    }
    if (!inuse[id] ) {
        return APR_NOTFOUND;
    }
    inuse[id] = 0;
    return APR_SUCCESS;
}