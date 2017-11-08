static void do_expand(request_rec *r, char *input, char *buffer, int nbuf,
                      backrefinfo *briRR, backrefinfo *briRC)
{
    char *inp, *outp;
    apr_size_t span, space;

    /*
     * for security reasons this expansion must be performed in a
     * single pass, otherwise an attacker can arrange for the result
     * of an earlier expansion to include expansion specifiers that
     * are interpreted by a later expansion, producing results that
     * were not intended by the administrator.
     */

    inp = input;
    outp = buffer;
    space = nbuf - 1; /* room for '\0' */

    for (;;) {
        span = strcspn(inp, "\\$%");
        if (span > space) {
            span = space;
        }
        memcpy(outp, inp, span);
        inp += span;
        outp += span;
        space -= span;
        if (space == 0 || *inp == '\0') {
            break;
        }
        /* now we have a '\', '$', or '%' */
        if (inp[0] == '\\') {
            if (inp[1] != '\0') {
                inp++;
                goto skip;
            }
        }
        else if (inp[1] == '{') {
            char *endp;
            endp = find_closing_bracket(inp+2, '{', '}');
            if (endp == NULL) {
                goto skip;
            }
            /*
            * These lookups may be recursive in a very convoluted
            * fashion -- see the LA-U and LA-F variable expansion
            * prefixes -- so we copy lookup keys to a separate buffer
            * rather than adding zero bytes in order to use them in
            * place.
            */
            if (inp[0] == '$') {
                /* ${...} map lookup expansion */
                /*
                * To make rewrite maps useful the lookup key and
                * default values must be expanded, so we make
                * recursive calls to do the work. For security
                * reasons we must never expand a string that includes
                * verbatim data from the network. The recursion here
                * isn't a problem because the result of expansion is
                * only passed to lookup_map() so it cannot be
                * re-expanded, only re-looked-up. Another way of
                * looking at it is that the recursion is entirely
                * driven by the syntax of the nested curly brackets.
                */
                char *map, *key, *dflt, *result;
                char xkey[MAX_STRING_LEN];
                char xdflt[MAX_STRING_LEN];
                key = find_char_in_brackets(inp+2, ':', '{', '}');
                if (key == NULL) {
                    goto skip;
                }
                map  = apr_pstrndup(r->pool, inp+2, key-inp-2);
                dflt = find_char_in_brackets(key+1, '|', '{', '}');
                if (dflt == NULL) {
                    key  = apr_pstrndup(r->pool, key+1, endp-key-1);
                    dflt = "";
                }
                else {
                    key  = apr_pstrndup(r->pool, key+1, dflt-key-1);
                    dflt = apr_pstrndup(r->pool, dflt+1, endp-dflt-1);
                }
                do_expand(r, key,  xkey,  sizeof(xkey),  briRR, briRC);
                result = lookup_map(r, map, xkey);
                if (result) {
                    span = apr_cpystrn(outp, result, space) - outp;
                }
                else {
                    do_expand(r, dflt, xdflt, sizeof(xdflt), briRR, briRC);
                    span = apr_cpystrn(outp, xdflt, space) - outp;
                }
            }
            else if (inp[0] == '%') {
                /* %{...} variable lookup expansion */
                char *var;
                var  = apr_pstrndup(r->pool, inp+2, endp-inp-2);
                span = apr_cpystrn(outp, lookup_variable(r, var), space) - outp;
            }
            else {
                span = 0;
            }
            inp = endp+1;
            outp += span;
            space -= span;
            continue;
        }
        else if (apr_isdigit(inp[1])) {
            int n = inp[1] - '0';
            backre