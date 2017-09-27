    if (rv == APR_SUCCESS) {
        rv = apr_dir_remove(dir, pool);
        if (APR_ENOTEMPTY == rv) {
            rv = APR_SUCCESS;
        }
        if (rv != APR_SUCCESS) {
            char errmsg[120];
            apr_file_printf(errfile, "Could not remove directory %s: %s" APR_EOL_STR,
                    dir, apr_strerror(rv, errmsg, sizeof errmsg));
        }
    }

    return rv;
}

