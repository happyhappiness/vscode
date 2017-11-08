static apr_status_t slotmem_do(ap_slotmem_instance_t *mem, ap_slotmem_callback_fn_t *func, void *data, apr_pool_t *pool)
{
    unsigned int i;
    void *ptr;
    char *inuse;
    apr_status_t retval = APR_SUCCESS;
    

    if (!mem)
        return APR_ENOSHMAVAIL;

    ptr = mem->base;
    inuse = mem->inuse;
    for (i = 0; i < mem->num; i++, inuse++) {
        if (!AP_SLOTMEM_IS_PREGRAB(mem) ||
           (AP_SLOTMEM_IS_PREGRAB(mem) && *inuse)) {
            retval = func((void *) ptr, data, pool);
            if (retval != APR_SUCCESS)
                break;
        }
        ptr += mem->size;
    }
    return retval;
}