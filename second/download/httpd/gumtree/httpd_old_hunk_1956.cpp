    if (alg == ALG_CRYPT) {
        alg = ALG_APMD5;
        apr_file_printf(errfile, "Automatically using MD5 format." NL);
    }
#endif

#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
    if (alg == ALG_PLAIN) {
        apr_file_printf(errfile,"Warning: storing passwords as plain text "
                        "might just not work on this platform." NL);
    }
#endif

