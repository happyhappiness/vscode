static apr_status_t crypto_shutdown(void)
{
    if (NSS_IsInitialized()) {
        SECStatus s = NSS_Shutdown();
        if (s != SECSuccess) {
            return APR_EINIT;
        }
    }
    return APR_SUCCESS;
}