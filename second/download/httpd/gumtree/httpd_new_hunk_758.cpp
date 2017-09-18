    apr_md5_ctx_t context;
    unsigned char digest[16];
    char string[MAX_STRING_LEN];
    char pwin[MAX_STRING_LEN];
    char pwv[MAX_STRING_LEN];
    unsigned int i;
    apr_size_t len = sizeof(pwin);

    if (apr_password_get("New password: ", pwin, &len) != APR_SUCCESS) {
	fprintf(stderr, "password too long");
	exit(5);
    }
    len = sizeof(pwin);
