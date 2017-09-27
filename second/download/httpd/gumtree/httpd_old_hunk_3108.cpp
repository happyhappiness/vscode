    for (i = 0; i < slot->desc.num; i++, inuse++) {
        if (!*inuse) {
            break;
        }
    }
    if (i >= slot->desc.num) {
        return APR_ENOSHMAVAIL;
    }
    *inuse = 1;
    *id = i;
    return APR_SUCCESS;
}

static apr_status_t slotmem_release(ap_slotmem_instance_t *slot,
                                    unsigned int id)
{
