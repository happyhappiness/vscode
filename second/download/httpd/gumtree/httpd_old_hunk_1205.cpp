         e = APR_BUCKET_NEXT(e))
    {
        const char *s;
        apr_size_t len;

        if (APR_BUCKET_IS_EOS(e)) {
            if (mobj->m_len > obj->count) {
                /* Caching a streamed response. Reallocate a buffer of the
                 * correct size and copy the streamed response into that
                 * buffer */
                mobj->m = realloc(mobj->m, obj->count);
                if (!mobj->m) {
