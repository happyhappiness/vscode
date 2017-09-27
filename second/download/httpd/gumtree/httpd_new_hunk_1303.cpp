    srand(seed);
    return rv;
}

static void putline(apr_file_t *f, const char *l)
{
    apr_status_t rc;
    rc = apr_file_puts(l, f);
    if (rc != APR_SUCCESS) {
        char errstr[MAX_STRING_LEN];
        apr_strerror(rc, errstr, MAX_STRING_LEN);
        apr_file_printf(errfile, "Error writing temp file: %s" NL, errstr);
        apr_file_close(f);
        exit(ERR_FILEPERM);
    }
}

/*
 * Make a password record from the given information.  A zero return
 * indicates success; failure means that the output buffer contains an
 * error message instead.
