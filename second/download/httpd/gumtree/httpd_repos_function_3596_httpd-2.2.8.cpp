static apr_status_t shm_cleanup(void* shm)
{
    apr_status_t rv = APR_SUCCESS;
    apr_shm_t *m = shm;
    
    if (!UnmapViewOfFile(m->memblk)) {
        rv = apr_get_os_error();
    }
    if (!CloseHandle(m->hMap)) {
        return (rv != APR_SUCCESS) ? rv : apr_get_os_error();
    }
    /* ### Do we want to make a point of unlinking m->file here? 
     * Need to add the fname to the apr_shm_t, in that case.
     */
    return rv;
}