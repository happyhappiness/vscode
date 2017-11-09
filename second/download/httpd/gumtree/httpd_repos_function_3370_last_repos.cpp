static apr_status_t shm_cleanup_wrapper(void *unused)
{
    if (exipc_shm)
        return apr_shm_destroy(exipc_shm);
    return OK;
}