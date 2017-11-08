static apr_status_t cleanup_file_cache(void *sconfv)
{
    a_server_config *sconf = sconfv;
    apr_pool_t *p = apr_hash_pool_get(sconf->fileht);
    a_file *file;
    apr_hash_index_t *hi;

    /* Iterate over the file hash table and clean up each entry */
    for (hi = apr_hash_first(p, sconf->fileht); hi; hi=apr_hash_next(hi)) {
        apr_hash_this(hi, NULL, NULL, (void **)&file);
#if APR_HAS_MMAP
        if (file->is_mmapped) { 
	    apr_mmap_delete(file->mm);
        } 
#endif 
#if APR_HAS_SENDFILE
        if (!file->is_mmapped) {
            apr_file_close(file->file); 
        }
#endif
    }
    return APR_SUCCESS;
}