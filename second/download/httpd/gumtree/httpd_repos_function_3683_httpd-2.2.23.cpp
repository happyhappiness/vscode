static apr_status_t resolve_ident(apr_finfo_t *finfo, const char *fname,
                                  apr_int32_t wanted, apr_pool_t *pool)
{
    apr_file_t *thefile = NULL;
    apr_status_t rv;
    /* 
     * NT5 (W2K) only supports symlinks in the same manner as mount points.
     * This code should eventually take that into account, for now treat
     * every reparse point as a symlink...
     *
     * We must open the file with READ_CONTROL if we plan to retrieve the
     * user, group or permissions.
     */
    
    if ((rv = apr_file_open(&thefile, fname, APR_OPENINFO
                          | ((wanted & APR_FINFO_LINK) ? APR_OPENLINK : 0)
                          | ((wanted & (APR_FINFO_PROT | APR_FINFO_OWNER))
                                ? APR_READCONTROL : 0),
                            APR_OS_DEFAULT, pool)) == APR_SUCCESS) {
        rv = apr_file_info_get(finfo, wanted, thefile);
        finfo->filehand = NULL;
        apr_file_close(thefile);
    }
    else if (APR_STATUS_IS_EACCES(rv) && (wanted & (APR_FINFO_PROT 
                                                  | APR_FINFO_OWNER))) {
        /* We have a backup plan.  Perhaps we couldn't grab READ_CONTROL?
         * proceed without asking for that permission...
         */
        if ((rv = apr_file_open(&thefile, fname, APR_OPENINFO
                              | ((wanted & APR_FINFO_LINK) ? APR_OPENLINK : 0),
                                APR_OS_DEFAULT, pool)) == APR_SUCCESS) {
            rv = apr_file_info_get(finfo, wanted & ~(APR_FINFO_PROT 
                                                 | APR_FINFO_OWNER),
                                 thefile);
            finfo->filehand = NULL;
            apr_file_close(thefile);
        }
    }

    if (rv != APR_SUCCESS && rv != APR_INCOMPLETE)
        return (rv);

    /* We picked up this case above and had opened the link's properties */
    if (wanted & APR_FINFO_LINK)
        finfo->valid |= APR_FINFO_LINK;

    return rv;
}