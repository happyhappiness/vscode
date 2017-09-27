        return APR_ENOSHMAVAIL;
    }

    inuse = slot->inuse;

    if (id >= slot->desc.num || !inuse[id] ) {
        return APR_NOTFOUND;
    }
    inuse[id] = 0;
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
    &slotmem_slot_size,
    &slotmem_grab,
    &slotmem_release
};

/* make the storage usuable from outside */
