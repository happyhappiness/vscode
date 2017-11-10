static int pipe_get_passwd_cb(char *buf, int length, char *prompt, int verify)
{
    apr_status_t rc;
    char *p;

    apr_file_puts(prompt, writetty);

    buf[0]='\0';
    rc = apr_file_gets(buf, length, readtty);
    apr_file_puts(APR_EOL_STR, writetty);

    if (rc != APR_SUCCESS || apr_file_eof(readtty)) {
        memset(buf, 0, length);
        return 1;  /* failure */
    }
    if ((p = strchr(buf, '\n')) != NULL) {
        *p = '\0';
    }
#ifdef WIN32
    /* XXX: apr_sometest */
    if ((p = strchr(buf, '\r')) != NULL) {
        *p = '\0';
    }
#endif
    return 0;
}