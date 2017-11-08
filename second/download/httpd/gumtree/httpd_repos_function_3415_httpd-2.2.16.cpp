static int warrsztoastr(const char * const * *retarr,
                        const wchar_t * arrsz, int args)
{
    const apr_wchar_t *wch;
    apr_size_t totlen;
    apr_size_t newlen;
    apr_size_t wsize;
    char **newarr;
    int arg;

    if (args < 0) {
        for (args = 1, wch = arrsz; wch[0] || wch[1]; ++wch)
            if (!*wch)
                ++args;
    }
    wsize = 1 + wch - arrsz;

    newarr = apr_malloc_dbg((args + 1) * sizeof(char *),
                            __FILE__, __LINE__);

    /* This is a safe max allocation, we will realloc after
     * processing and return the excess to the free store.
     * 3 ucs bytes hold any single wchar_t value (16 bits)
     * 4 ucs bytes will hold a wchar_t pair value (20 bits)
     */
    newlen = totlen = wsize * 3 + 1;
    newarr[0] = apr_malloc_dbg(newlen * sizeof(char),
                               __FILE__, __LINE__);

    (void)apr_conv_ucs2_to_utf8(arrsz, &wsize,
                                newarr[0], &newlen);

    assert(newlen && !wsize);
    /* Return to the free store if the heap realloc is the least bit optimized
     */
    newarr[0] = apr_realloc_dbg(newarr[0], totlen - newlen,
                                __FILE__, __LINE__);

    for (arg = 1; arg < args; ++arg) {
        newarr[arg] = newarr[arg - 1] + 2;
        while (*(newarr[arg]++)) {
            /* continue */;
        }
    }

    newarr[arg] = NULL;

    *retarr = newarr;
    return args;
}