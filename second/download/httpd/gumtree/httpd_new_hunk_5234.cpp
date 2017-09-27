    if (rv == APR_SUCCESS) {
        rv = apr_dir_remove(dir, pool);
        if (APR_ENOTEMPTY == rv) {
            rv = APR_SUCCESS;
        }
        if (rv != APR_SUCCESS) {
            apr_file_printf(errfile, "Could not remove directory %s: %pm" APR_EOL_STR,
                    dir, &rv);
        }
    }

    return rv;
}

