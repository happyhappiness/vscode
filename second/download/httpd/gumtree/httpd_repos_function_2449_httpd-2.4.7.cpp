static void slotmem_shm_initialize_cleanup(apr_pool_t *p)
{
    apr_pool_cleanup_register(p, &globallistmem, cleanup_slotmem,
                              apr_pool_cleanup_null);
}