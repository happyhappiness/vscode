        rv = apr_shm_attach(&shm, fname, gpool);
    }
    else {
        rv = APR_EINVAL;
    }
    if (rv == APR_SUCCESS) {
        /* check size */
        if (apr_shm_size_get(shm) != size) {
            apr_shm_detach(shm);
            return APR_EINVAL;
        }
        ptr = (char *)apr_shm_baseaddr_get(shm);
        memcpy(&desc, ptr, sizeof(desc));
        if (desc.size != item_size || desc.num != item_num) {
            apr_shm_detach(shm);
            return APR_EINVAL;
        }
        ptr += AP_SLOTMEM_OFFSET;
    }
    else {
        apr_size_t dsize = size - AP_SLOTMEM_OFFSET;
