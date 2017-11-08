apr_status_t mpm_service_set_name(apr_pool_t *p, const char **display_name,
                                  const char *set_name)
{
    char key_name[MAX_PATH];
    ap_regkey_t *key;
    apr_status_t rv;

    /* ### Needs improvement, on Win2K the user can _easily_
     * change the display name to a string that doesn't reflect
     * the internal service name + whitespace!
     */
    mpm_service_name = apr_palloc(p, strlen(set_name) + 1);
    apr_collapse_spaces((char*) mpm_service_name, set_name);
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        apr_size_t slen = strlen(mpm_service_name) + 1;
        apr_size_t wslen = slen;
        mpm_service_name_w = apr_palloc(p, wslen * sizeof(apr_wchar_t));
        rv = apr_conv_utf8_to_ucs2(mpm_service_name, &slen,
                                   mpm_service_name_w, &wslen);
        if (rv != APR_SUCCESS)
            return rv;
        else if (slen)
            return APR_ENAMETOOLONG;
    }
#endif /* APR_HAS_UNICODE_FS */

    apr_snprintf(key_name, sizeof(key_name), SERVICECONFIG, mpm_service_name);
    rv = ap_regkey_open(&key, AP_REGKEY_LOCAL_MACHINE, key_name, APR_READ, pconf);
    if (rv == APR_SUCCESS) {
        rv = ap_regkey_value_get(&mpm_display_name, key, "DisplayName", pconf);
        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        /* Take the given literal name if there is no service entry */
        mpm_display_name = apr_pstrdup(p, set_name);
    }
    *display_name = mpm_display_name;

    return rv;
}