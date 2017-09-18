#if defined(WIN32) || defined(OS2) || defined(NETWARE)
        strcasecmp(apr_filename_of_pathname(name), "nul") != 0) {
#else
        strcmp(name, "/dev/null") != 0) {
#endif /* WIN32 || OS2 */
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
                     "Access to file %s denied by server: not a regular file",
                     name);
        apr_file_close(file);
        return APR_EBADF;
    }

#ifdef WIN32
    /* Some twisted character [no pun intended] at MS decided that a
