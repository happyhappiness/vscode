apr_file_printf(errfile, " -m  Force MD5 encryption of the password"
#if defined(WIN32) || defined(TPF) || defined(NETWARE)
        " (default)"
#endif
        ".\n");