static char *ap_ssi_parse_string(request_rec *r, include_ctx_t *ctx, 
                                 const char *in, char *out,
                                 apr_size_t length, int leave_name)
{
    char ch;
    char *next;
    char *end_out;
    apr_size_t out_size;

    /* allocate an output buffer if needed */
    if (!out) {
        out_size = PARSE_STRING_INITIAL_SIZE;
        if (out_size > length) {
            out_size = length;
        }
        out = apr_palloc(r->pool, out_size);
    }
    else {
        out_size = length;
    }

    /* leave room for nul terminator */
    end_out = out + out_size - 1;

    next = out;
    while ((ch = *in++) != '\0') {
        switch (ch) {
        case '\\':
            if (next == end_out) {
                if (out_size < length) {
                    /* double the buffer size */
                    apr_size_t new_out_size = out_size * 2;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                else {
                    /* truncated */
                    *next = '\0';
                    return out;
                }
            }
            if (*in == '$') {
                *next++ = *in++;
            }
            else {
                *next++ = ch;
            }
            break;
        case '$':
            {
                const char *start_of_var_name;
                char *end_of_var_name;        /* end of var name + 1 */
                const char *expansion, *temp_end, *val;
                char        tmp_store;
                apr_size_t l;

                /* guess that the expansion won't happen */
                expansion = in - 1;
                if (*in == '{') {
                    ++in;
                    start_of_var_name = in;
                    in = ap_strchr_c(in, '}');
                    if (in == NULL) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                                      0, r, "Missing '}' on variable \"%s\"",
                                      expansion);
                        *next = '\0';
                        return out;
                    }
                    temp_end = in;
                    end_of_var_name = (char *)temp_end;
                    ++in;
                }
                else {
                    start_of_var_name = in;
                    while (apr_isalnum(*in) || *in == '_') {
                        ++in;
                    }
                    temp_end = in;
                    end_of_var_name = (char *)temp_end;
                }
                /* what a pain, too bad there's no table_getn where you can
                 * pass a non-nul terminated string */
                l = end_of_var_name - start_of_var_name;
                if (l != 0) {
                    tmp_store        = *end_of_var_name;
                    *end_of_var_name = '\0';
                    val = get_include_var(r, ctx, start_of_var_name);
                    *end_of_var_name = tmp_store;

                    if (val) {
                        expansion = val;
                        l = strlen(expansion);
                    }
                    else if (leave_name) {
                        l = in - expansion;
                    }
                    else {
                        /* no expansion to be done */
                        break;
                    }
                }
                else {
                    /* zero-length variable name causes just the $ to be 
                     * copied */
                    l = 1;
                }
                if ((next + l > end_out) && (out_size < length)) {
                    /* increase the buffer size to accommodate l more chars */
                    apr_size_t new_out_size = out_size;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    do {
                        new_out_size *= 2;
                    } while (new_out_size < current_length + l + 1); /* +1 for NUL */
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                l = ((int)l > end_out - next) ? (end_out - next) : l;
                memcpy(next, expansion, l);
                next += l;
                break;
            }
        default:
            if (next == end_out) {
                if (out_size < length) {
                    /* double the buffer size */
                    apr_size_t new_out_size = out_size * 2;
                    apr_size_t current_length = next - out;
                    char *new_out;
                    if (new_out_size > length) {
                        new_out_size = length;
                    }
                    new_out = apr_palloc(r->pool, new_out_size);
                    memcpy(new_out, out, current_length);
                    out = new_out;
                    out_size = new_out_size;
                    end_out = out + out_size - 1;
                    next = out + current_length;
                }
                else {
                    /* truncated */
                    *next = '\0';
                    return out;
                }
            }
            *next++ = ch;
            break;
        }
    }
    *next = '\0';
    return out;
}