static int post_config(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp,
                       server_rec *s)
{
    slotmem_shm_initialize_cleanup(p);
    return OK;
}