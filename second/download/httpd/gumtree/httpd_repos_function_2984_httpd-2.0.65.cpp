apr_status_t filepath_drive_get(char **rootpath, char drive, 
                                apr_int32_t flags, apr_pool_t *p)
{
    char path[APR_PATH_MAX];
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        apr_wchar_t *ignored;
        apr_wchar_t wdrive[8];
        apr_wchar_t wpath[APR_PATH_MAX];
        apr_status_t rv;
        /* ???: This needs review, apparently "\\?\d:." returns "\\?\d:" 
         * as if that is useful for anything.
         */
        wcscpy(wdrive, L"D:.");
        wdrive[0] = (apr_wchar_t)(unsigned char)drive;
        if (!GetFullPathNameW(wdrive, sizeof(wpath) / sizeof(apr_wchar_t), wpath, &ignored))
            return apr_get_os_error();
        if ((rv = unicode_to_utf8_path(path, sizeof(path), wpath)))
            return rv;
    }
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        char *ignored;
        char drivestr[4];
        drivestr[0] = drive;
        drivestr[1] = ':';
        drivestr[2] = '.';;
        drivestr[3] = '\0';
        if (!GetFullPathName(drivestr, sizeof(path), path, &ignored))
            return apr_get_os_error();
    }
#endif
    if (!(flags & APR_FILEPATH_NATIVE)) {
        for (*rootpath = path; **rootpath; ++*rootpath) {
            if (**rootpath == '\\')
                **rootpath = '/';
        }
    }
    *rootpath = apr_pstrdup(p, path);
    return APR_SUCCESS;
}