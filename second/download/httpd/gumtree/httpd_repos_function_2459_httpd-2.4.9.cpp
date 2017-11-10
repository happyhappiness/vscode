static apr_status_t slotmem_grab(ap_slotmem_instance_t *slot, unsigned int *id)
{
    unsigned int i;
    char *inuse;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse;

    for (i = 0; i < slot->num; i++, inuse++) {
        if (!*inuse) {
            break;
        }
    }
    if (i >= slot->num) {
        return APR_EINVAL;
    }
    *inuse = 1;
    *id = i;
    return APR_SUCCESS;
}