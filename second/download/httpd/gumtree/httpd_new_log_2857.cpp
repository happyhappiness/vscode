fprintf(stderr, "ab: Could not stat POST data file (%s): %s\n", pfile,
                apr_strerror(rv, errmsg, sizeof errmsg));