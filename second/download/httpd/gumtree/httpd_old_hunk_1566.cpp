        ret[outlen] = '\0';
    }

    return ret;
}


/*
 * +-------------------------------------------------------+
 * |                                                       |
 * |              Conditional Expression Parser
 * |                                                       |
 * +-------------------------------------------------------+
 */

static APR_INLINE int re_check(include_ctx_t *ctx, const char *string,
                               const char *rexp)
{
    ap_regex_t *compiled;
    backref_t *re = ctx->intern->re;

    compiled = ap_pregcomp(ctx->dpool, rexp, AP_REG_EXTENDED);
    if (!compiled) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, ctx->intern->r, "unable to "
                      "compile pattern \"%s\"", rexp);
        return -1;
    }

    if (!re) {
        re = ctx->intern->re = apr_palloc(ctx->pool, sizeof(*re));
    }

    re->source = apr_pstrdup(ctx->pool, string);
    re->rexp = apr_pstrdup(ctx->pool, rexp);
    re->nsub = compiled->re_nsub;
    re->have_match = !ap_regexec(compiled, string, AP_MAX_REG_MATCH, 
                                 re->match, 0);

    ap_pregfree(ctx->dpool, compiled);
    return re->have_match;
}

static int get_ptoken(include_ctx_t *ctx, const char **parse, token_t *token, token_t *previous)
{
    const char *p;
    apr_size_t shift;
    int unmatched;

    token->value = NULL;

    if (!*parse) {
        return 0;
    }

    /* Skip leading white space */
    while (apr_isspace(**parse)) {
        ++*parse;
    }

    if (!**parse) {
        *parse = NULL;
        return 0;
    }

    TYPE_TOKEN(token, TOKEN_STRING); /* the default type */
    p = *parse;
    unmatched = 0;

    switch (*(*parse)++) {
    case '(':
        TYPE_TOKEN(token, TOKEN_LBRACE);
        return 0;
    case ')':
        TYPE_TOKEN(token, TOKEN_RBRACE);
        return 0;
    case '=':
        if (**parse == '=') ++*parse;
        TYPE_TOKEN(token, TOKEN_EQ);
        return 0;
    case '!':
        if (**parse == '=') {
            TYPE_TOKEN(token, TOKEN_NE);
            ++*parse;
            return 0;
        }
        TYPE_TOKEN(token, TOKEN_NOT);
        return 0;
    case '\'':
        unmatched = '\'';
        break;
    case '/':
        /* if last token was ACCESS, this token is STRING */
        if (previous != NULL && TOKEN_ACCESS == previous->type) {
            break;
        }
        TYPE_TOKEN(token, TOKEN_RE);
        unmatched = '/';
        break;
    case '|':
        if (**parse == '|') {
            TYPE_TOKEN(token, TOKEN_OR);
            ++*parse;
            return 0;
        }
        break;
    case '&':
        if (**parse == '&') {
            TYPE_TOKEN(token, TOKEN_AND);
            ++*parse;
            return 0;
        }
        break;
    case '>':
        if (**parse == '=') {
            TYPE_TOKEN(token, TOKEN_GE);
            ++*parse;
            return 0;
        }
        TYPE_TOKEN(token, TOKEN_GT);
        return 0;
    case '<':
        if (**parse == '=') {
            TYPE_TOKEN(token, TOKEN_LE);
            ++*parse;
            return 0;
        }
        TYPE_TOKEN(token, TOKEN_LT);
        return 0;
    case '-':
        if (**parse == 'A' && (ctx->intern->accessenable)) {
            TYPE_TOKEN(token, TOKEN_ACCESS);
            ++*parse;
            return 0;
        }
        break;
    }

    /* It's a string or regex token
     * Now search for the next token, which finishes this string
     */
    shift = 0;
    p = *parse = token->value = unmatched ? *parse : p;

    for (; **parse; p = ++*parse) {
        if (**parse == '\\') {
            if (!*(++*parse)) {
                p = *parse;
                break;
            }

            ++shift;
        }
        else {
            if (unmatched) {
                if (**parse == unmatched) {
                    unmatched = 0;
                    ++*parse;
                    break;
                }
            } else if (apr_isspace(**parse)) {
                break;
            }
            else {
                int found = 0;

                switch (**parse) {
                case '(':
                case ')':
                case '=':
                case '!':
                case '<':
                case '>':
                    ++found;
                    break;

                case '|':
                case '&':
                    if ((*parse)[1] == **parse) {
                        ++found;
                    }
                    break;
                }

                if (found) {
                    break;
                }
            }
        }
    }

    if (unmatched) {
        token->value = apr_pstrdup(ctx->dpool, "");
    }
    else {
        apr_size_t len = p - token->value - shift;
        char *c = apr_palloc(ctx->dpool, len + 1);

        p = token->value;
        token->value = c;

        while (shift--) {
            const char *e = ap_strchr_c(p, '\\');

            memcpy(c, p, e-p);
            c   += e-p;
            *c++ = *++e;
            len -= e-p;
            p    = e+1;
        }

        if (len) {
            memcpy(c, p, len);
        }
        c[len] = '\0';
    }

    return unmatched;
}

static int parse_expr(include_ctx_t *ctx, const char *expr, int *was_error)
{
    parse_node_t *new, *root = NULL, *current = NULL;
    request_rec *r = ctx->intern->r;
    request_rec *rr = NULL;
    const char *error = "Invalid expression \"%s\" in file %s";
    const char *parse = expr;
    unsigned regex = 0;

    *was_error = 0;

    if (!parse) {
        return 0;
    }

    /* Create Parse Tree */
    while (1) {
        /* uncomment this to see how the tree a built:
         *
         * DEBUG_DUMP_TREE(ctx, root);
         */
        CREATE_NODE(ctx, new);

        {
#ifdef DEBUG_INCLUDE
            int was_unmatched =
#endif
            get_ptoken(ctx, &parse, &new->token,
                       (current != NULL ? &current->token : NULL));
            if (!parse)
                break;

            DEBUG_DUMP_UNMATCHED(ctx, was_unmatched);
            DEBUG_DUMP_TOKEN(ctx, &new->token);
        }

        if (!current) {
            switch (new->token.type) {
            case TOKEN_STRING:
            case TOKEN_NOT:
            case TOKEN_ACCESS:
            case TOKEN_LBRACE:
                root = current = new;
                continue;

            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,
                              r->filename);
                *was_error = 1;
                return 0;
            }
        }

        switch (new->token.type) {
        case TOKEN_STRING:
            switch (current->token.type) {
            case TOKEN_STRING:
                current->token.value =
                    apr_pstrcat(ctx->dpool, current->token.value,
                                *current->token.value ? " " : "",
                                new->token.value, NULL);
                continue;

            case TOKEN_RE:
            case TOKEN_RBRACE:
            case TOKEN_GROUP:
                break;

            default:
                new->parent = current;
                current = current->right = new;
                continue;
            }
            break;

        case TOKEN_RE:
            switch (current->token.type) {
            case TOKEN_EQ:
            case TOKEN_NE:
                new->parent = current;
                current = current->right = new;
                ++regex;
                continue;

            default:
                break;
            }
            break;

        case TOKEN_AND:
        case TOKEN_OR:
            switch (current->token.type) {
            case TOKEN_STRING:
            case TOKEN_RE:
            case TOKEN_GROUP:
                current = current->parent;

                while (current) {
                    switch (current->token.type) {
                    case TOKEN_AND:
                    case TOKEN_OR:
                    case TOKEN_LBRACE:
                        break;

                    default:
                        current = current->parent;
                        continue;
                    }
                    break;
                }

                if (!current) {
                    new->left = root;
                    root->parent = new;
                    current = root = new;
                    continue;
                }

                new->left = current->right;
                new->left->parent = new;
                new->parent = current;
                current = current->right = new;
                continue;

            default:
                break;
            }
            break;

        case TOKEN_EQ:
        case TOKEN_NE:
        case TOKEN_GE:
        case TOKEN_GT:
        case TOKEN_LE:
        case TOKEN_LT:
            if (current->token.type == TOKEN_STRING) {
                current = current->parent;

                if (!current) {
                    new->left = root;
                    root->parent = new;
                    current = root = new;
                    continue;
                }

                switch (current->token.type) {
                case TOKEN_LBRACE:
                case TOKEN_AND:
                case TOKEN_OR:
                    new->left = current->right;
                    new->left->parent = new;
                    new->parent = current;
                    current = current->right = new;
                    continue;

                default:
                    break;
                }
            }
            break;

        case TOKEN_RBRACE:
            while (current && current->token.type != TOKEN_LBRACE) {
                current = current->parent;
            }

            if (current) {
                TYPE_TOKEN(&current->token, TOKEN_GROUP);
                continue;
            }

            error = "Unmatched ')' in \"%s\" in file %s";
            break;

        case TOKEN_NOT:
        case TOKEN_ACCESS:
        case TOKEN_LBRACE:
            switch (current->token.type) {
            case TOKEN_STRING:
            case TOKEN_RE:
            case TOKEN_RBRACE:
            case TOKEN_GROUP:
                break;

            default:
                current->right = new;
                new->parent = current;
                current = new;
                continue;
            }
            break;

        default:
            break;
        }

        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr, r->filename);
        *was_error = 1;
        return 0;
    }

    DEBUG_DUMP_TREE(ctx, root);

    /* Evaluate Parse Tree */
    current = root;
    error = NULL;
    while (current) {
        switch (current->token.type) {
        case TOKEN_STRING:
            current->token.value =
                ap_ssi_parse_string(ctx, current->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);
            current->value = !!*current->token.value;
            break;

        case TOKEN_AND:
        case TOKEN_OR:
            if (!current->left || !current->right) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return 0;
            }

            if (!current->left->done) {
                switch (current->left->token.type) {
                case TOKEN_STRING:
                    current->left->token.value =
                        ap_ssi_parse_string(ctx, current->left->token.value,
                                            NULL, 0, SSI_EXPAND_DROP_NAME);
                    current->left->value = !!*current->left->token.value;
                    DEBUG_DUMP_EVAL(ctx, current->left);
                    current->left->done = 1;
                    break;

                default:
                    current = current->left;
                    continue;
                }
            }

            /* short circuit evaluation */
            if (!current->right->done && !regex &&
                ((current->token.type == TOKEN_AND && !current->left->value) ||
                (current->token.type == TOKEN_OR && current->left->value))) {
                current->value = current->left->value;
            }
            else {
                if (!current->right->done) {
                    switch (current->right->token.type) {
                    case TOKEN_STRING:
                        current->right->token.value =
                            ap_ssi_parse_string(ctx,current->right->token.value,
                                                NULL, 0, SSI_EXPAND_DROP_NAME);
                        current->right->value = !!*current->right->token.value;
                        DEBUG_DUMP_EVAL(ctx, current->right);
                        current->right->done = 1;
                        break;

                    default:
                        current = current->right;
                        continue;
                    }
                }

                if (current->token.type == TOKEN_AND) {
                    current->value = current->left->value &&
                                     current->right->value;
                }
                else {
                    current->value = current->left->value ||
                                     current->right->value;
                }
            }
            break;

        case TOKEN_EQ:
        case TOKEN_NE:
            if (!current->left || !current->right ||
                current->left->token.type != TOKEN_STRING ||
                (current->right->token.type != TOKEN_STRING &&
                 current->right->token.type != TOKEN_RE)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return 0;
            }
            current->left->token.value =
                ap_ssi_parse_string(ctx, current->left->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);
            current->right->token.value =
                ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);

            if (current->right->token.type == TOKEN_RE) {
                current->value = re_check(ctx, current->left->token.value,
                                          current->right->token.value);
                --regex;
            }
            else {
                current->value = !strcmp(current->left->token.value,
                                         current->right->token.value);
            }

            if (current->token.type == TOKEN_NE) {
                current->value = !current->value;
            }
            break;

        case TOKEN_GE:
        case TOKEN_GT:
        case TOKEN_LE:
        case TOKEN_LT:
            if (!current->left || !current->right ||
                current->left->token.type != TOKEN_STRING ||
                current->right->token.type != TOKEN_STRING) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return 0;
            }

            current->left->token.value =
                ap_ssi_parse_string(ctx, current->left->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);
            current->right->token.value =
                ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);

            current->value = strcmp(current->left->token.value,
                                    current->right->token.value);

            switch (current->token.type) {
            case TOKEN_GE: current->value = current->value >= 0; break;
            case TOKEN_GT: current->value = current->value >  0; break;
            case TOKEN_LE: current->value = current->value <= 0; break;
            case TOKEN_LT: current->value = current->value <  0; break;
            default: current->value = 0; break; /* should not happen */
            }
            break;

        case TOKEN_NOT:
        case TOKEN_GROUP:
            if (current->right) {
                if (!current->right->done) {
                    current = current->right;
                    continue;
                }
                current->value = current->right->value;
            }
            else {
                current->value = 1;
            }

            if (current->token.type == TOKEN_NOT) {
                current->value = !current->value;
            }
            break;

        case TOKEN_ACCESS:
            if (current->left || !current->right ||
                (current->right->token.type != TOKEN_STRING &&
                 current->right->token.type != TOKEN_RE)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s: Token '-A' must be followed by a URI string.",
                            expr, r->filename);
                *was_error = 1;
                return 0;
            }
            current->right->token.value =
                ap_ssi_parse_string(ctx, current->right->token.value, NULL, 0,
                                    SSI_EXPAND_DROP_NAME);
            rr = ap_sub_req_lookup_uri(current->right->token.value, r, NULL);
            /* 400 and higher are considered access denied */
            if (rr->status < HTTP_BAD_REQUEST) {
                current->value = 1;
            }
            else {
                current->value = 0;
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rr->status, r, 
                              "mod_include: The tested "
                              "subrequest -A \"%s\" returned an error code.",
                              current->right->token.value);
            }
            ap_destroy_sub_req(rr);
            break;

        case TOKEN_RE:
            if (!error) {
                error = "No operator before regex in expr \"%s\" in file %s";
            }
        case TOKEN_LBRACE:
            if (!error) {
                error = "Unmatched '(' in \"%s\" in file %s";
            }
        default:
            if (!error) {
                error = "internal parser error in \"%s\" in file %s";
            }

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, expr,r->filename);
            *was_error = 1;
            return 0;
        }

        DEBUG_DUMP_EVAL(ctx, current);
        current->done = 1;
        current = current->parent;
    }

    return (root ? root->value : 0);
}


/*
 * +-------------------------------------------------------+
 * |                                                       |
 * |                    Action Handlers
 * |                                                       |
 * +-------------------------------------------------------+
