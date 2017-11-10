static void error_bucket_destroy(void *data)
{
    ap_bucket_error *h = data;

    if (apr_bucket_shared_destroy(h)) {
        apr_bucket_free(h);
    }
}