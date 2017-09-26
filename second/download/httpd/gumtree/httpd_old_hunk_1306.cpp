        cleanup_tempfile_and_exit(1);
    }
    pw = pwin;
    apr_file_printf(f, "%s:%s:", user, realm);

    /* Do MD5 stuff */
    sprintf(string, "%s:%s:%s", user, realm, pw);

    apr_md5_init(&context);
#if APR_CHARSET_EBCDIC
    apr_md5_set_xlate(&context, to_ascii);
#endif
    apr_md5_update(&context, (unsigned char *) string, strlen(string));
