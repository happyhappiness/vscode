static void lob_bucket_destroy(void *data)
{
    apr_bucket_lob *f = data;

    if (apr_bucket_shared_destroy(f)) {
        /* no need to destroy database objects here; it will get
         * done automatically when the pool gets cleaned up */
        apr_bucket_free(f);
    }
}