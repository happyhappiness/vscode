static apr_off_t get_body(char *buffer, apr_size_t *len, const char *tag,
                          apr_file_t *map)
{
    char *endbody;
    int bodylen;
    int taglen;
    apr_off_t pos;

    taglen = strlen(tag);
    *len -= taglen;

    /* We are at the first character following a body:tag\n entry
     * Suck in the body, then backspace to the first char after the
     * closing tag entry.  If we fail to read, find the tag or back
     * up then we have a hosed file, so give up already
     */
    if (apr_file_read(map, buffer, len) != APR_SUCCESS) {
        return -1;
    }

    /* put a copy of the tag *after* the data read from the file
     * so that strstr() will find something with no reliance on
     * terminating '\0'
     */
    memcpy(buffer + *len, tag, taglen);
    endbody = strstr(buffer, tag);
    if (endbody == buffer + *len) {
        return -1;
    }
    bodylen = endbody - buffer;
    endbody += taglen;
    /* Skip all the trailing cruft after the end tag to the next line */
    while (*endbody) {
        if (*endbody == '\n') {
            ++endbody;
            break;
        }
        ++endbody;
    }

    pos = -(apr_off_t)(*len - (endbody - buffer));
    if (apr_file_seek(map, APR_CUR, &pos) != APR_SUCCESS) {
        return -1;
    }

    /* Give the caller back the actual body's file offset and length */
    *len = bodylen;
    return pos - (endbody - buffer);
}