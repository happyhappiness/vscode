static void file_bucket_destroy(void *data)
{
    apr_bucket_file *f = data;

    if (apr_bucket_shared_destroy(f)) {
        /* no need to close the file here; it will get
         * done automatically when the pool gets cleaned up */
        apr_bucket_free(f);
    }
}