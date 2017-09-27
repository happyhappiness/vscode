    while ((rv = apr_file_gets(argsbuffer, HUGE_STRING_LEN,
                               script_err)) == APR_SUCCESS) {
        newline = strchr(argsbuffer, '\n');
        if (newline) {
            *newline = '\0';
        }
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01215)
                      "%s", argsbuffer);
    }

    return rv;
}

