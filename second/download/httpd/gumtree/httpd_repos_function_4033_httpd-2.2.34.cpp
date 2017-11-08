static apr_status_t atomic_cleanup(void *data)
{
    if (hash_mutex == data)
        hash_mutex = NULL;

    return APR_SUCCESS;
}