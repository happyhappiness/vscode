     * we're in better shape.
     */
    if (!ctx) {
        char *token;
        const char *encoding;

        /* We have checked above that bb is not empty */
        e = APR_BRIGADE_LAST(bb);
        if (APR_BUCKET_IS_EOS(e)) {
            /*
             * If we already know the size of the response, we can skip
             * compression on responses smaller than the compression overhead.
