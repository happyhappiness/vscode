static void mmap_bucket_destroy(void *data)
{
    apr_bucket_mmap *m = data;

    if (apr_bucket_shared_destroy(m)) {
        if (m->mmap) {
            apr_pool_cleanup_kill(m->mmap->cntxt, m, mmap_bucket_cleanup);
            apr_mmap_delete(m->mmap);
        }
        apr_bucket_free(m);
    }
}