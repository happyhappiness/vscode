static apr_status_t slotmem_fgrab(ap_slotmem_instance_t *slot, unsigned int id)
{
    char *inuse;
    
    if (!slot) {
        return APR_ENOSHMAVAIL;
    }
    
    if (id >= slot->num) {
        return APR_EINVAL;
    }
    inuse = slot->inuse + id;
    *inuse = 1;
    return APR_SUCCESS;
}