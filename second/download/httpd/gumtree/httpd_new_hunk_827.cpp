
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
