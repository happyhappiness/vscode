static apr_status_t shm_attach_internal(apr_shm_t **m,
                                        const char *file,
                                        apr_pool_t *pool,
                                        int global)
{
    HANDLE hMap;
    void *mapkey;
    void *base;

    /* res_name_from_filename turns file into a pseudo-name
     * without slashes or backslashes, and prepends the \global
     * or local prefix on Win2K and later
     */
    mapkey = res_name_from_filename(file, global, pool);

#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
#ifndef _WIN32_WCE
        hMap = OpenFileMappingW(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, mapkey);
#else
        /* The WCE 3.0 lacks OpenFileMapping. So we emulate one with
         * opening the existing shmem and reading its size from the header 
         */
        hMap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, 
                                  PAGE_READWRITE, 0, sizeof(apr_shm_t), mapkey);
#endif
    }
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        hMap = OpenFileMappingA(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, mapkey);
    }
#endif

    if (!hMap) {
        return apr_get_os_error();
    }
    
    base = MapViewOfFile(hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (!base) {
        CloseHandle(hMap);
        return apr_get_os_error();
    }
    
    *m = (apr_shm_t *) apr_palloc(pool, sizeof(apr_shm_t));
    (*m)->pool = pool;
    (*m)->memblk = base;
    /* Real (*m)->mem->size could be recovered with VirtualQuery */
    (*m)->size = (*m)->memblk->size;
#if _WIN32_WCE
    /* Reopen with real size  */
    UnmapViewOfFile(base);
    CloseHandle(hMap);

    hMap = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, 
                              PAGE_READWRITE, 0, (*m)->size, mapkey);
    if (!hMap) {
        return apr_get_os_error();
    }
    base = MapViewOfFile(hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if (!base) {
        CloseHandle(hMap);
        return apr_get_os_error();
    }    
#endif
    (*m)->hMap = hMap;
    (*m)->length = (*m)->memblk->length;
    (*m)->usrmem = (char*)base + sizeof(memblock_t);
    (*m)->filename = NULL;

    apr_pool_cleanup_register((*m)->pool, *m, 
                              shm_cleanup, apr_pool_cleanup_null);
    return APR_SUCCESS;
}