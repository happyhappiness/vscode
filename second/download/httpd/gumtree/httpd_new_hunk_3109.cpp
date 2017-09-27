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

static const ap_slotmem_provider_t storage = {
    "sharedmem",
    &slotmem_doall,
    &slotmem_create,
    &slotmem_attach,
    &slotmem_dptr,
    &slotmem_get,
    &slotmem_put,
    &slotmem_num_slots,
    &slotmem_num_free_slots,
    &slotmem_slot_size,
    &slotmem_grab,
    &slotmem_release
};

/* make the storage usuable from outside */
