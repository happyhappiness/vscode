void *res_name_from_filename(const char *file, int global, apr_pool_t *pool)
{
#if APR_HAS_UNICODE_FS
    IF_WIN_OS_IS_UNICODE
    {
        apr_wchar_t *wpre, *wfile, *ch;
        apr_size_t n = strlen(file) + 1;
        apr_size_t r, d;
        apr_status_t rv;

        if (apr_os_level >= APR_WIN_2000) {
            if (global)
                wpre = L"Global\\";
            else
                wpre = L"Local\\";
        }
        else
            wpre = L"";
        r = wcslen(wpre);

        if (n > 256 - r) {
            file += n - 256 - r;
            n = 256;
            /* skip utf8 continuation bytes */
            while ((*file & 0xC0) == 0x80) {
                ++file;
                --n;
            }
        }
        wfile = apr_palloc(pool, (r + n) * sizeof(apr_wchar_t));
        wcscpy(wfile, wpre);
        d = n;
        if (rv = apr_conv_utf8_to_ucs2(file, &n, wfile + r, &d)) {
            return NULL;
        }
        for (ch = wfile + r; *ch; ++ch) {
            if (*ch == ':' || *ch == '/' || *ch == '\\')
                *ch = '_';
        }
        return wfile;
    }
#endif
#if APR_HAS_ANSI_FS
    ELSE_WIN_OS_IS_ANSI
    {
        char *nfile, *ch;
        apr_size_t n = strlen(file) + 1;

#if !APR_HAS_UNICODE_FS
        apr_status_t rv;
        apr_size_t r, d;
        char *pre;

        if (apr_os_level >= APR_WIN_2000) {
            if (global)
                pre = "Global\\";
            else
                pre = "Local\\";
        }
        else
            pre = "";
        r = strlen(pre);

        if (n > 256 - r) {
            file += n - 256 - r;
            n = 256;
        }
        nfile = apr_palloc(pool, (r + n) * sizeof(apr_wchar_t));
        memcpy(nfile, pre, r);
        memcpy(nfile + r, file, n);
#else
        const apr_size_t r = 0;
        if (n > 256) {
            file += n - 256;
            n = 256;
        }
        nfile = apr_pmemdup(pool, file, n);
#endif
        for (ch = nfile + r; *ch; ++ch) {
            if (*ch == ':' || *ch == '/' || *ch == '\\')
                *ch = '_';
        }
        return nfile;
    }
#endif
}