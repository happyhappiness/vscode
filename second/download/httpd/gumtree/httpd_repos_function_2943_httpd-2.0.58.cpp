apr_status_t filepath_root_case(char **rootpath, char *root, apr_pool_t *p)
{
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        apr_wchar_t *ignored;
        apr_wchar_t wpath[APR_PATH_MAX];
        apr_status_t rv;
        apr_wchar_t wroot[APR_PATH_MAX];
        /* ???: This needs review, apparently "\\?\d:." returns "\\?\d:" 
         * as if that is useful for anything.
         */
        if (rv = utf8_to_unicode_path(wroot, sizeof(wroot) 
                                           / sizeof(apr_wchar_t), root))
            return rv;
        if (!GetFullPathNameW(wroot, sizeof(wpath) / sizeof(apr_wchar_t), wpath, &ignored))
            return apr_get_os_error();

        /* Borrow wroot as a char buffer (twice as big as necessary) 
         */
        if ((rv = unicode_to_utf8_path((char*)wroot, sizeof(wroot), wpath)))
            return rv;
        *rootpath = apr_pstrdup(p, (char*)wroot);
    }
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        char path[APR_PATH_MAX];
        char *ignored;
        if (!GetFullPathName(root, sizeof(path), path, &ignored))
            return apr_get_os_error();
        *rootpath = apr_pstrdup(p, path);
    }
#endif
    return APR_SUCCESS;
}