    if (rv != APR_SUCCESS) {
        fprintf(stderr, "ab: Could not open POST data file (%s): %s\n", pfile,
                apr_strerror(rv, errmsg, sizeof errmsg));
        return rv;
    }

    apr_file_info_get(&finfo, APR_FINFO_NORM, postfd);
    postlen = (apr_size_t)finfo.size;
    postdata = malloc(postlen);
    if (!postdata) {
        fprintf(stderr, "ab: Could not allocate POST data buffer\n");
        return APR_ENOMEM;
    }
