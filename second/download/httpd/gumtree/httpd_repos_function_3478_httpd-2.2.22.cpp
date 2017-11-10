int apr_wastrtoastr(char const * const * *retarr, 
                    wchar_t const * const *arr, int args)
{
    apr_size_t elesize = 0;
    char **newarr;
    char *elements;
    char *ele;
    int arg;

    if (args < 0) {
        for (args = 0; arr[args]; ++args)
            ;
    }

    newarr = apr_malloc_dbg((args + 1) * sizeof(char *),
                            __FILE__, __LINE__);

    for (arg = 0; arg < args; ++arg) {
        newarr[arg] = (void*)(wcslen(arr[arg]) + 1);
        elesize += (apr_size_t)newarr[arg];
    }

    /* This is a safe max allocation, we will realloc after
     * processing and return the excess to the free store.
     * 3 ucs bytes hold any single wchar_t value (16 bits)
     * 4 ucs bytes will hold a wchar_t pair value (20 bits)
     */
    elesize = elesize * 3 + 1;
    ele = elements = apr_malloc_dbg(elesize * sizeof(char),
                                    __FILE__, __LINE__);

    for (arg = 0; arg < args; ++arg) {
        apr_size_t len = (apr_size_t)newarr[arg];
        apr_size_t newlen = elesize;

        newarr[arg] = ele;
        (void)apr_conv_ucs2_to_utf8(arr[arg], &len,
                                    newarr[arg], &elesize);

        newlen -= elesize;
        ele += newlen;
        assert(elesize && (len == 0));
    }

    newarr[arg] = NULL;
    *(ele++) = '\0';

    /* Return to the free store if the heap realloc is the least bit optimized
     */
    ele = apr_realloc_dbg(elements, ele - elements,
                          __FILE__, __LINE__);

    if (ele != elements) {
        apr_size_t diff = ele - elements;
        for (arg = 0; arg < args; ++arg) {
            newarr[arg] += diff;
        }
    }

    *retarr = (char const * const *)newarr;
    return args;
}