static char *subst_prefix_path(request_rec *r, char *input, const char *match,
                               const char *subst)
{
    apr_size_t len = strlen(match);

    if (len && match[len - 1] == '/') {
        --len;
    }

    if (!strncmp(input, match, len) && input[len++] == '/') {
        apr_size_t slen, outlen;
        char *output;

        rewritelog((r, 5, NULL, "strip matching prefix: %s -> %s", input,
                    input+len));

        slen = strlen(subst);
        if (slen && subst[slen - 1] != '/') {
            ++slen;
        }

        outlen = strlen(input) + slen - len;
        output = apr_palloc(r->pool, outlen + 1); /* don't forget the \0 */

        memcpy(output, subst, slen);
        if (slen && !output[slen-1]) {
            output[slen-1] = '/';
        }
        memcpy(output+slen, input+len, outlen - slen);
        output[outlen] = '\0';

        rewritelog((r, 4, NULL, "add subst prefix: %s -> %s", input+len,
                    output));

        return output;
    }

    /* prefix didn't match */
    return input;
}