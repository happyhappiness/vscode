static char *do_expand(char *input, rewrite_ctx *ctx, rewriterule_entry *entry)
{
    result_list *result, *current;
    result_list sresult[SMALL_EXPANSION];
    unsigned spc = 0;
    apr_size_t span, inputlen, outlen;
    char *p, *c;
    apr_pool_t *pool = ctx->r->pool;

    span = strcspn(input, "\\$%");
    inputlen = strlen(input);

    /* fast exit */
    if (inputlen == span) {
        return apr_pstrdup(pool, input);
    }

    /* well, actually something to do */
    result = current = &(sresult[spc++]);

    p = input + span;
    current->next = NULL;
    current->string = input;
    current->len = span;
    outlen = span;

    /* loop for specials */
    do {
        /* prepare next entry */
        if (current->len) {
            current->next = (spc < SMALL_EXPANSION)
                            ? &(sresult[spc++])
                            : (result_list *)apr_palloc(pool,
                                                        sizeof(result_list));
            current = current->next;
            current->next = NULL;
            current->len = 0;
        }

        /* escaped character */
        if (*p == '\\') {
            current->len = 1;
            ++outlen;
            if (!p[1]) {
                current->string = p;
                break;
            }
            else {
                current->string = ++p;
                ++p;
            }
        }

        /* variable or map lookup */
        else if (p[1] == '{') {
            char *endp;

            endp = find_closing_curly(p+2);
            if (!endp) {
                current->len = 2;
                current->string = p;
                outlen += 2;
                p += 2;
            }

            /* variable lookup */
            else if (*p == '%') {
                p = lookup_variable(apr_pstrmemdup(pool, p+2, endp-p-2), ctx);

                span = strlen(p);
                current->len = span;
                current->string = p;
                outlen += span;
                p = endp + 1;
            }

            /* map lookup */
            else {     /* *p == '$' */
                char *key;

                /*
                 * To make rewrite maps useful, the lookup key and
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

                key = find_char_in_curlies(p+2, ':');
                if (!key) {
                    current->len = 2;
                    current->string = p;
                    outlen += 2;
                    p += 2;
                }
                else {
                    char *map, *dflt;

                    map = apr_pstrmemdup(pool, p+2, endp-p-2);
                    key = map + (key-p-2);
                    *key++ = '\0';
                    dflt = find_char_in_curlies(key, '|');
                    if (dflt) {
                        *dflt++ = '\0';
                    }

                    /* reuse of key variable as result */
                    key = lookup_map(ctx->r, map, do_expand(key, ctx, entry));

                    if (!key && dflt && *dflt) {
                        key = do_expand(dflt, ctx, entry);
                    }

                    if (key) {
                        span = strlen(key);
                        current->len = span;
                        current->string = key;
                        outlen += span;
                    }

                    p = endp + 1;
                }
            }
        }

        /* backreference */
        else if (apr_isdigit(p[1])) {
         