static char *find_title(request_rec *r)
{
    char titlebuf[MAX_STRING_LEN], *find = "<title>";
    apr_file_t *thefile = NULL;
    int x, y, p;
    apr_size_t n;

    if (r->status != HTTP_OK) {
        return NULL;
    }
    if ((r->content_type != NULL)
        && (response_is_html(r)
            || !strcmp(r->content_type, INCLUDES_MAGIC_TYPE))
        && !r->content_encoding) {
        if (apr_file_open(&thefile, r->filename, APR_READ,
                          APR_OS_DEFAULT, r->pool) != APR_SUCCESS) {
            return NULL;
        }
        n = sizeof(char) * (MAX_STRING_LEN - 1);
        apr_file_read(thefile, titlebuf, &n);
        if (n == 0) {
            apr_file_close(thefile);
            return NULL;
        }
        titlebuf[n] = '\0';
        for (x = 0, p = 0; titlebuf[x]; x++) {
            if (apr_tolower(titlebuf[x]) == find[p]) {
                if (!find[++p]) {
                    if ((p = ap_ind(&titlebuf[++x], '<')) != -1) {
                        titlebuf[x + p] = '\0';
                    }
                    /* Scan for line breaks for Tanmoy's secretary */
                    for (y = x; titlebuf[y]; y++) {
                        if ((titlebuf[y] == CR) || (titlebuf[y] == LF)) {
                            if (y == x) {
                                x++;
                            }
                            else {
                                titlebuf[y] = ' ';
                            }
                        }
                    }
                    apr_file_close(thefile);
                    return apr_pstrdup(r->pool, &titlebuf[x]);
                }
            }
            else {
                p = 0;
            }
        }
        apr_file_close(thefile);
    }
    return NULL;
}