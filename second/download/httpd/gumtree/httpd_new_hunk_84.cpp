        }
        if (fd == 1 && !other && eos) {
            apr_file_t *tmpfile;
            const char *name;
            /* Open a new XTHREAD handle to the file */
            apr_file_name_get(&name, file);
            mobj->flags = ((APR_SENDFILE_ENABLED & apr_file_flags_get(file))
                           | APR_READ | APR_BINARY | APR_XTHREAD | APR_FILE_NOCLEANUP);
            rv = apr_file_open(&tmpfile, name, mobj->flags,
                               APR_OS_DEFAULT, r->pool);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            apr_file_unset_inherit(tmpfile);
            apr_os_file_get(&(mobj->fd), tmpfile);

            /* Open for business */
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server,
                         "mem_cache: Cached file: %s with key: %s", name, obj->key);
            obj->complete = 1;
            return APR_SUCCESS;
        }

        /* Content not suitable for fd caching. Cache in-memory instead. */
        mobj->type = CACHE_TYPE_HEAP;
    }

    /* 
     * FD cacheing is not enabled or the content was not
     * suitable for fd caching.
     */  
