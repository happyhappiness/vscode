static enum header_state get_header_line(char *buffer, int len, apr_file_t *map)
{
    char *buf_end = buffer + len;
    char *cp;
    char c;

    /* Get a noncommented line */

    do {
        if (apr_file_gets(buffer, MAX_STRING_LEN, map) != APR_SUCCESS) {
            return header_eof;
        }
    } while (buffer[0] == '#');

    /* If blank, just return it --- this ends information on this variant */

    for (cp = buffer; (*cp && apr_isspace(*cp)); ++cp) {
        continue;
    }

    if (*cp == '\0') {
        return header_sep;
    }

    /* If non-blank, go looking for header lines, but note that we still
     * have to treat comments specially...
     */

    cp += strlen(cp);

    /* We need to shortcut the rest of this block following the Body:
     * tag - we will not look for continutation after this line.
     */
    if (!strncasecmp(buffer, "Body:", 5))
        return header_seen;

    while (apr_file_getc(&c, map) != APR_EOF) {
        if (c == '#') {
            /* Comment line */
            while (apr_file_getc(&c, map) != APR_EOF && c != '\n') {
                continue;
            }
        }
        else if (apr_isspace(c)) {
            /* Leading whitespace.  POSSIBLE continuation line
             * Also, possibly blank --- if so, we ungetc() the final newline
             * so that we will pick up the blank line the next time 'round.
             */

            while (c != '\n' && apr_isspace(c)) {
                if(apr_file_getc(&c, map) != APR_SUCCESS)
                    break;
            }

            apr_file_ungetc(c, map);

            if (c == '\n') {
                return header_seen;     /* Blank line */
            }

            /* Continuation */

            while (   cp < buf_end - 2
                   && (apr_file_getc(&c, map)) != APR_EOF
                   && c != '\n') {
                *cp++ = c;
            }

            *cp++ = '\n';
            *cp = '\0';
        }
        else {

            /* Line beginning with something other than whitespace */

            apr_file_ungetc(c, map);
            return header_seen;
        }
    }

    return header_seen;
}