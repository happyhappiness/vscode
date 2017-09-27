    
    if (!slot) {
        return APR_ENOSHMAVAIL;
    }

    if (id >= slot->desc.num) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02397)
                     "slotmem(%s) fgrab failed. Num %u/num_free %u",
                     slot->name, slotmem_num_slots(slot),
                     slotmem_num_free_slots(slot));
        return APR_EINVAL;
    }
    inuse = slot->inuse + id;
