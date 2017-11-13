static apr_status_t slotmem_release(ap_slotmem_instance_t *slot,
                                    unsigned int id)
{
    char *inuse;

    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse;

    if (id >= slot->desc.num || !inuse[id] ) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02294)
                     "slotmem(%s) release failed. Num %u/inuse[%u] %d",
                     slot->name, slotmem_num_slots(slot),
                     id, (int)inuse[id]);
        return APR_NOTFOUND;
    }
    inuse[id] = 0;
    (*slot->num_free)++;
    return APR_SUCCESS;
}