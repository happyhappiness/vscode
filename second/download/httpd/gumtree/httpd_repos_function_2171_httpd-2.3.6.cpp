static apr_status_t slotmem_dptr(ap_slotmem_instance_t *score, unsigned int id, void **mem)
{

    void *ptr;

    if (!score)
        return APR_ENOSHMAVAIL;
    if (id < 0 || id >= score->num)
        return APR_ENOSHMAVAIL;

    ptr = score->base + score->size * id;
    if (!ptr)
        return APR_ENOSHMAVAIL;
    *mem = ptr;
    return APR_SUCCESS;
}