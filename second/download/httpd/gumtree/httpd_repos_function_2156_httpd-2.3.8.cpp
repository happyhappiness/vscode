static apr_status_t cleanup_slotmem(void *param)
{
    ap_slotmem_instance_t **mem = param;
    apr_pool_t *pool = NULL;

    if (*mem) {
        ap_slotmem_instance_t *next = *mem;
        pool = next->gpool;
        while (next) {
            store_slotmem(next);
            apr_shm_destroy((apr_shm_t *)next->shm);
            next = next->next;
        }
        apr_pool_destroy(pool);
    }
    return APR_SUCCESS;
}