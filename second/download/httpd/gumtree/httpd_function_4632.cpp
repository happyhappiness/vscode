static apr_status_t slotmem_grab(ap_slotmem_instance_t *slot, unsigned int *id)
{
    unsigned int i;
    char *inuse;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse;

    for (i = 0; i < slot->desc.num; i++, inuse++) {
        if (!*inuse) {
            break;
        }
    }
    if (i >= slot->desc.num) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02293)
                     "slotmem(%s) grab failed. Num %u/num_free %u",
                     slot->name, slotmem_num_slots(slot),
                     slotmem_num_free_slots(slot));
        return APR_EINVAL;
    }
    *inuse = 1;
    *id = i;
    (*slot->num_free)--;
    return APR_SUCCESS;
}