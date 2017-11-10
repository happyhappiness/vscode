static apr_status_t regkey_cleanup(void *key)
{
    ap_regkey_t *regkey = key;

    if (regkey->hkey && regkey->hkey != INVALID_HANDLE_VALUE) {
        RegCloseKey(regkey->hkey);
        regkey->hkey = INVALID_HANDLE_VALUE;
    }
    return APR_SUCCESS;
}