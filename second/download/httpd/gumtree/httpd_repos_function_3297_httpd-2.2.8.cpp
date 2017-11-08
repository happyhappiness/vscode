int apr_canonical_error(apr_status_t err)
{
    int rv = -1, index;

    if (err < APR_OS_START_SYSERR)
        return err;

    err -= APR_OS_START_SYSERR;

    for (index=0; index<MAPSIZE && errormap[index][0] != err; index++);
    
    if (index<MAPSIZE)
        rv = errormap[index][1];
    else
        fprintf(stderr, "apr_canonical_error: Unknown OS/2 error code %d\n", err );
        
    return rv;
}