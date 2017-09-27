    }
#endif /*APR_CHARSET_EBCDIC*/

    check_args(pool, argc, argv, &alg, &mask, &user, &pwfilename, &password);


#if !CRYPT_ALGO_SUPPORTED
    if (alg == ALG_CRYPT) {
        alg = ALG_APMD5;
        apr_file_printf(errfile, "Automatically using MD5 format." NL);
    }
#endif

#if CRYPT_ALGO_SUPPORTED
    if (alg == ALG_PLAIN) {
        apr_file_printf(errfile,"Warning: storing passwords as plain text "
                        "might just not work on this platform." NL);
    }
#endif

