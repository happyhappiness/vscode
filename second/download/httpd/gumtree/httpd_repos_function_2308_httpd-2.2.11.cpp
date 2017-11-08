apr_status_t ap_registry_get_server_root(apr_pool_t *p, char **buf)
{
    apr_status_t rv;
    ap_regkey_t *key;

    if ((rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, PRODREGKEY,
                             APR_READ, p)) == APR_SUCCESS) {
        rv = ap_regkey_value_get(buf, key, "ServerRoot", p);
        ap_regkey_close(key);
        if (rv == APR_SUCCESS)
            return rv;
    }

    if ((rv = ap_regkey_open(&key, AP_REGKEY_CURRENT_USER, PRODREGKEY,
                             APR_READ, p)) == APR_SUCCESS) {
        rv = ap_regkey_value_get(buf, key, "ServerRoot", p);
        ap_regkey_close(key);
        if (rv == APR_SUCCESS)
            return rv;
    }

    *buf = NULL;
    return rv;
}