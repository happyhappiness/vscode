static int warrsztoastr(const char * const * *retarr,
                        const wchar_t * arrsz, int args)
{
    const apr_wchar_t *wch;
    apr_size_t totlen;
    apr_size_t newlen;
    apr_size_t wsize;
    char **env;
    char *pstrs;
    char *strs;
    int arg;

    if (args < 0) {
        for (args = 1, wch = arrsz; wch[0] || wch[1]; ++wch)
            if (!*wch)
                ++args;
    }
    wsize = 1 + wch - arrsz;

    /* This is a safe max allocation, we will alloc each
     * string exactly after processing and return this
     * temporary buffer to the free store.
     * 3 ucs bytes hold any single wchar_t value (16 bits)
     * 4 ucs bytes will hold a wchar_t pair value (20 bits)
     */
    newlen = totlen = wsize * 3 + 1;
    pstrs = strs = apr_malloc_dbg(newlen * sizeof(char),
                                  __FILE__, __LINE__);

    (void)apr_conv_ucs2_to_utf8(arrsz, &wsize, strs, &newlen);

    assert(newlen && !wsize);

    *retarr = env = apr_malloc_dbg((args + 1) * sizeof(char*),
                                   __FILE__, __LINE__);
    for (arg = 0; arg < args; ++arg) {
        char* p = pstrs;
        int len = 0;
        while (*p++)
            ++len;
        len += 1;

        *env = apr_malloc_dbg(len * sizeof(char),
                              __FILE__, __LINE__);
        memcpy(*env, pstrs, len * sizeof(char));

        pstrs += len;
        ++env;
    }

    *env = NULL;
    free(strs);

    return args;
}