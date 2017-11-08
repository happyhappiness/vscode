static apr_status_t crypto_shutdown(void)
{
    ERR_free_strings();
    EVP_cleanup();
    ENGINE_cleanup();
    return APR_SUCCESS;
}