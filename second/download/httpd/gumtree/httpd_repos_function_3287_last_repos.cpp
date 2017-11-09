static apr_status_t cleanup_slotmem(void *param)
{
    ap_slotmem_instance_t **mem = param;

    if (*mem) {
        ap_slotmem_instance_t *next = *mem;
        while (next) {
            if (AP_SLOTMEM_IS_PERSIST(next)) {
                store_slotmem(next);
            }
            apr_shm_destroy((apr_shm_t *)next->shm);
            if (next->fbased) {
                apr_shm_remove(next->name, next->gpool);
                apr_file_remove(next->name, next->gpool);
            }
            next = next->next;
        }
    }
    /* apr_pool_destroy(gpool); */
    globallistmem = NULL;
    return APR_SUCCESS;
}