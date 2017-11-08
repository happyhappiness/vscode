static apr_status_t shm_cleanup(void* shm)
{
    apr_status_t rv = APR_SUCCESS;
    apr_shm_t *m = shm;
    
    if (!UnmapViewOfFile(m->memblk)) {
        rv = apr_get_os_error();
    }
    if (!CloseHandle(m->hMap)) {
        rv = rv != APR_SUCCESS ? rv : apr_get_os_error();
    }
    if (m->filename) {
        /* Remove file if file backed */
        apr_status_t rc = apr_file_remove(m->filename, m->pool);
        rv = rv != APR_SUCCESS ? rv : rc;
    }
    return rv;
}