static void add_password(const char *user, const char *realm, apr_file_t *f)
{
    char *pw;
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
    apr_password_get("Re-type new password: ", pwv, &len);
    if (strcmp(pwin, pwv) != 0) {
	fprintf(stderr, "They don't match, sorry.\n");
	if (tfp) {
	    apr_file_close(tfp);
	}
	exit(1);
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
    apr_md5_final(digest, &context);

    for (i = 0; i < 16; i++)
	apr_file_printf(f, "%02x", digest[i]);

    apr_file_printf(f, "\n");
}