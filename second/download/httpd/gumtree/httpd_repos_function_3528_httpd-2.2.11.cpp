apr_status_t apr_file_info_get_locked(apr_finfo_t *finfo, apr_int32_t wanted,
                                      apr_file_t *thefile)
{
    struct_stat info;

    if (thefile->buffered) {
        apr_status_t rv = apr_file_flush_locked(thefile);
        if (rv != APR_SUCCESS)
            return rv;
    }

    if (fstat(thefile->filedes, &info) == 0) {
        finfo->pool = thefile->pool;
        finfo->fname = thefile->fname;
        fill_out_finfo(finfo, &info, wanted);
        return (wanted & ~finfo->valid) ? APR_INCOMPLETE : APR_SUCCESS;
    }
    else {
        return errno;
    }
}