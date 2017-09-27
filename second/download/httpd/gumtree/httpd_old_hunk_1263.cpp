        }
        rv = apr_bucket_read(e, &s, &len, eblock);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        if (len) {
            /* Check for buffer overflow */
           if ((obj->count + len) > mobj->m_len) {
               return APR_ENOMEM;
           }
           else {
               memcpy(cur, s, len);
               cur+=len;
               obj->count+=len;
