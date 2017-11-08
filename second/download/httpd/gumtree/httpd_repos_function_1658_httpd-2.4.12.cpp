static apr_status_t array_getstr(void *buf, size_t bufsize, void *param)
{
    array_contents_t *ml = (array_contents_t *) param;
    char *buffer = (char *) buf;
    char next = '\0';
    size_t i = 0;
    apr_status_t rc = APR_SUCCESS;

    /* read chars from stream, stop on newline */
    while (i < bufsize - 1 && next != LF &&
           ((rc = array_getch(&next, param)) == APR_SUCCESS)) {
        buffer[i++] = next;
    }

    if (rc == APR_EOF) {
        /* maybe update to next, possibly a recursion */
        if (next_one(ml)) {
            ap_assert(ml->next->getstr);
            /* keep next line count in sync! the caller will update
               the current line_number, we need to forward to the next */
            ml->next->line_number++;
            return ml->next->getstr(buf, bufsize, ml->next->param);
        }
        /* else that is really all we can do */
        return APR_EOF;
    }

    buffer[i] = '\0';

    return APR_SUCCESS;
}