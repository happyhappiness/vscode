static apr_status_t slotmem_dptr(ap_slotmem_instance_t *score, unsigned int id, void **mem)
{

    char *ptr;

    if (!score)
        return APR_ENOSHMAVAIL;
    if (id >= score->num)
        return APR_EINVAL;

    ptr = (char *)score->base + score->size * id;
    if (!ptr)
        return APR_ENOSHMAVAIL;
    *mem = ptr;
    return APR_SUCCESS;
}