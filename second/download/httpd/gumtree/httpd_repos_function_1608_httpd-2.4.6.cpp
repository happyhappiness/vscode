static int fix_encoding(request_rec *r)
{
    const char *enc = r->content_encoding;
    char *x_enc = NULL;
    apr_array_header_t *accept_encodings;
    accept_rec *accept_recs;
    int i;

    if (!enc || !*enc) {
        return DECLINED;
    }

    if (enc[0] == 'x' && enc[1] == '-') {
        enc += 2;
    }

    if ((accept_encodings = do_header_line(r->pool,
             apr_table_get(r->headers_in, "Accept-Encoding"))) == NULL) {
        return DECLINED;
    }

    accept_recs = (accept_rec *) accept_encodings->elts;

    for (i = 0; i < accept_encodings->nelts; ++i) {
        char *name = accept_recs[i].name;

        if (!strcmp(name, enc)) {
            r->content_encoding = name;
            return OK;
        }

        if (name[0] == 'x' && name[1] == '-' && !strcmp(name+2, enc)) {
            x_enc = name;
        }
    }

    if (x_enc) {
        r->content_encoding = x_enc;
        return OK;
    }

    return DECLINED;
}