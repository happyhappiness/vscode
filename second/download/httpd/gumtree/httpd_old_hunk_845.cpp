        }
        if (fd == 1 && !other && eos) {
            apr_file_t *tmpfile;
            const char *name;
            /* Open a new XTHREAD handle to the file */
            apr_file_name_get(&name, file);
            rv = apr_file_open(&tmpfile, name, 
                               APR_READ | APR_BINARY | APR_XTHREAD | APR_FILE_NOCLEANUP,
                               APR_OS_DEFAULT, r->pool);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            apr_file_unset_inherit(tmpfile);
            apr_os_file_get(&(mobj->fd), tmpfile);

            /* Open for business */
            obj->complete = 1;
            return APR_SUCCESS;
        }

        /* Content not suitable for fd caching. Cache in-memory instead. */
        mobj->type = CACHE_TYPE_HEAP;
        /* Check to make sure the object will not exceed configured thresholds */
        if (mobj->m_len < sconf->min_cache_object_size || 
            mobj->m_len > sconf->max_cache_object_size) {
            return APR_ENOMEM; /* ?? DECLINED; */
        }
        if ((sconf->cache_size + mobj->m_len) > sconf->max_cache_size) {
            return APR_ENOMEM; /* ?? DECLINED; */
        }
        sconf->cache_size += mobj->m_len;
    }

    /* 
     * FD cacheing is not enabled or the content was not
     * suitable for fd caching.
     */  
