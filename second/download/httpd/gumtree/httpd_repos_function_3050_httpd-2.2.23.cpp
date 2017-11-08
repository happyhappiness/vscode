static apr_status_t crypto_shutdown_helper(void *data)
{
    return crypto_shutdown();
}