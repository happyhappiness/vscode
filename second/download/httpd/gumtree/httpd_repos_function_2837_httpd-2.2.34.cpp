static void odbc_lob_bucket_destroy(void *data)
{
    odbc_bucket *bd = data;

    if (apr_bucket_shared_destroy(bd))
        apr_bucket_free(bd);
}