size_t
regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size)
{
    const char *msg;
    size_t msg_size;

    if (errcode < 0
            || errcode >= (sizeof(re_error_msg) / sizeof(re_error_msg[0])))
        /* Only error codes returned by the rest of the code should be passed
         * to this routine.  If we are given anything else, or if other regex
         * code generates an invalid error code, then the program has a bug.
         * Dump core so we can fix it.  */
        abort();

    msg = re_error_msg[errcode];

    /* POSIX doesn't require that we do anything in this case, but why
     * not be nice.  */
    if (!msg)
        msg = "Success";

    msg_size = strlen(msg) + 1; /* Includes the null.  */

    if (errbuf_size != 0) {
        if (msg_size > errbuf_size) {
            strncpy(errbuf, msg, errbuf_size - 1);
            errbuf[errbuf_size - 1] = 0;
        } else
            strcpy(errbuf, msg);
    }
    return msg_size;
}