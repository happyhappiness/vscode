    }

    if (sbuf && *sbuf)
        apr_file_printf(f, "%s\n", sbuf);

    first = 1;
    APR_BRIGADE_FOREACH(e, bb) {
        if (APR_BUCKET_IS_EOS(e)) {
            break;
        }
        rv = apr_bucket_read(e, &buf, &len, APR_BLOCK_READ);
        if (rv != APR_SUCCESS || (len == 0)) {
            break;
