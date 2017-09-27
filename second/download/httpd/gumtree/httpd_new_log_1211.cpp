fprintf(stderr, "ab: Could not open POST data file (%s): %s\n", pfile,
                apr_strerror(rv, errmsg, sizeof errmsg));