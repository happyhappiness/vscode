static int gettemp(char *path, apr_file_t **doopen, apr_int32_t flags, apr_pool_t *p)
{
    register char *start, *trv, *suffp;
    char *pad;
    apr_finfo_t sbuf;
    apr_status_t rv;
    apr_uint32_t randnum;

    if (randseed==0) {
        randseed = (int)apr_time_now();
        seedrandom(randseed);
    }

    for (trv = path; *trv; ++trv)
        ;
    suffp = trv;
    --trv;
    if (trv < path) {
        return APR_EINVAL;
    }

    /* Fill space with random characters */
    while (*trv == 'X') {
        randnum = arc4random() % (sizeof(padchar) - 1);
        *trv-- = padchar[randnum];
    }
    start = trv + 1;

    /*
     * check the target directory.
     */
    for (;; --trv) {
        if (trv <= path)
            break;
        if (*trv == '/') {
            *trv = '\0';
            rv = apr_stat(&sbuf, path, APR_FINFO_TYPE, p);
            *trv = '/';
            if (rv != APR_SUCCESS)
                return rv;
            if (sbuf.filetype != APR_DIR) {
                return APR_ENOTDIR;
            }
            break;
        }
    }

    for (;;) {
        if ((rv = apr_file_open(doopen, path, flags,
                                APR_UREAD | APR_UWRITE, p)) == APR_SUCCESS)
            return APR_SUCCESS;
        if (!APR_STATUS_IS_EEXIST(rv))
            return rv;

        /* If we have a collision, cycle through the space of filenames */
        for (trv = start;;) {
            if (*trv == '\0' || trv == suffp)
                return APR_EINVAL; /* XXX: is this the correct return code? */
            pad = strchr((char *)padchar, *trv);
            if (pad == NULL || !*++pad) {
                *trv++ = padchar[0];
            }
            else {
                *trv++ = *pad;
                break;
            }
        }
    }
    /*NOTREACHED*/
}