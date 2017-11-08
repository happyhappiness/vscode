static char *apr_caret_escape_args(apr_pool_t *p, const char *str)
{
    char *cmd;
    unsigned char *d;
    const unsigned char *s;

    cmd = apr_palloc(p, 2 * strlen(str) + 1);	/* Be safe */
    d = (unsigned char *)cmd;
    s = (const unsigned char *)str;
    for (; *s; ++s) {

        /* 
         * Newlines to Win32/OS2 CreateProcess() are ill advised.
         * Convert them to spaces since they are effectively white
         * space to most applications
         */
	if (*s == '\r' || *s == '\n') {
	    *d++ = ' ';
            continue;
	}

	if (IS_SHCHAR(*s)) {
	    *d++ = '^';
	}
	*d++ = *s;
    }
    *d = '\0';

    return cmd;
}