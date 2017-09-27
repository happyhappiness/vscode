            const char *remove;
            apr_status_t status;

            remove = apr_pstrcat(pool, base, "/", header, NULL);
            status = apr_file_remove(remove, pool);
            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                apr_file_printf(errfile, "Could not remove file %s: %pm" APR_EOL_STR,
                        remove, &status);
                rv = status;
            }

            remove = apr_pstrcat(pool, base, "/", data, NULL);
            status = apr_file_remove(remove, pool);
            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                apr_file_printf(errfile, "Could not remove file %s: %pm" APR_EOL_STR,
                        remove, &status);
                rv = status;
            }

            status = remove_directory(pool, apr_pstrcat(pool, base, "/", vdir, NULL));
            if (status != APR_SUCCESS && !APR_STATUS_IS_ENOENT(status)) {
                rv = status;
