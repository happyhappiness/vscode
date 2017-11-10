static char *substitute(char *buf,
                        const int bufsize,
                        const char *name,
                        const char *replacement, const int do_esc)
{
    int lbuf = strlen(buf),
        lname = strlen(name),
        lrepl = strlen(replacement),
        lsubs = lrepl +
        (do_esc ? (2 + number_of_escapes(DELIM, replacement)) : 0),
        shift = lsubs - lname, size = lbuf + shift, i, j;

    /* buf must starts with name */
    ap_assert(!strncmp(buf, name, lname));

    /* hmmm??? */
    if (!strcmp(name, replacement))
        return NULL;

    debug(fprintf(stderr,
                  "substitute(%s,%s,%s,%d,sh=%d,lbuf=%d,lrepl=%d,lsubs=%d)\n",
                  buf, name, replacement, do_esc, shift, lbuf, lrepl, lsubs));

    if (size >= bufsize) {
        /* could/should I reallocate? */
        return "cannot substitute, buffer size too small";
    }

    /* cannot use strcpy as strings may overlap */
    if (shift != 0) {
        memmove(buf + lname + shift, buf + lname, lbuf - lname + 1);
    }

    /* insert the replacement with escapes */
    j = 0;
    if (do_esc)
        buf[j++] = DELIM;
    for (i = 0; i < lrepl; i++, j++) {
        if (do_esc && (replacement[i] == DELIM || replacement[i] == ESCAPE))
            buf[j++] = ESCAPE;
        buf[j] = replacement[i];
    }
    if (do_esc)
        buf[j++] = DELIM;

    return NULL;
}