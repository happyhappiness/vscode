static int parse_expr(request_rec *r, include_ctx_t *ctx, const char *expr,
                      int *was_error, int *was_unmatched, char *debug)
{
    struct parse_node {
        struct parse_node *left, *right, *parent;
        struct token token;
        int value, done;
    } *root, *current, *new;
    const char *parse;
    char* buffer;
    int retval = 0;
    apr_size_t debug_pos = 0;

    debug[debug_pos] = '\0';
    *was_error       = 0;
    *was_unmatched   = 0;
    if ((parse = expr) == (char *) NULL) {
        return (0);
    }
    root = current = (struct parse_node *) NULL;

    /* Create Parse Tree */
    while (1) {
        new = (struct parse_node *) apr_palloc(r->pool,
                                           sizeof(struct parse_node));
        new->parent = new->left = new->right = (struct parse_node *) NULL;
        new->done = 0;
        if ((parse = get_ptoken(r, parse, &new->token, was_unmatched)) == 
            (char *) NULL) {
            break;
        }
        switch (new->token.type) {

        case token_string:
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], 
                                  "     Token: string (%s)\n", 
                                  new->token.value);
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            switch (current->token.type) {
            case token_string:
                current->token.value = apr_pstrcat(r->pool,
                                                   current->token.value,
                                                   current->token.value[0] ? " " : "",
                                                   new->token.value,
                                                   NULL);
                                                   
                break;
            case token_eq:
            case token_ne:
            case token_and:
            case token_or:
            case token_lbrace:
            case token_not:
            case token_ge:
            case token_gt:
            case token_le:
            case token_lt:
                new->parent = current;
                current = current->right = new;
                break;
            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_re:
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], 
                                  "     Token: regex (%s)\n", 
                                  new->token.value);
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            switch (current->token.type) {
            case token_eq:
            case token_ne:
            case token_and:
            case token_or:
            case token_lbrace:
            case token_not:
                new->parent = current;
                current = current->right = new;
                break;
            default:
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_and:
        case token_or:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: and/or\n",
                    sizeof ("     Token: and/or\n"));
            debug_pos += sizeof ("     Token: and/or\n");
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            /* Percolate upwards */
            while (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_string:
                case token_re:
                case token_group:
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    current = current->parent;
                    continue;
                case token_lbrace:
                    break;
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
                break;
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                new->left->parent = new;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_not:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Token: not\n",
                    sizeof("     Token: not\n"));
            debug_pos += sizeof("     Token: not\n");
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            /* Percolate upwards */
            if (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_lbrace:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    break;
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "Invalid expression \"%s\" in file %s",
                                  expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_eq:
        case token_ne:
        case token_ge:
        case token_gt:
        case token_le:
        case token_lt:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Token: eq/ne/ge/gt/le/lt\n",
                    sizeof("     Token: eq/ne/ge/gt/le/lt\n"));
            debug_pos += sizeof("     Token: eq/ne/ge/gt/le/lt\n");
#endif
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            /* Percolate upwards */
            while (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_string:
                case token_re:
                case token_group:
                    current = current->parent;
                    continue;
                case token_lbrace:
                case token_and:
                case token_or:
                    break;
                case token_not:
                case token_eq:
                case token_ne:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
                break;
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                new->left->parent = new;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;

        case token_rbrace:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: rbrace\n",
                    sizeof ("     Token: rbrace\n"));
            debug_pos += sizeof ("     Token: rbrace\n");
#endif
            while (current != (struct parse_node *) NULL) {
                if (current->token.type == token_lbrace) {
                    current->token.type = token_group;
                    break;
                }
                current = current->parent;
            }
            if (current == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Unmatched ')' in \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            break;

        case token_lbrace:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Token: lbrace\n",
                    sizeof ("     Token: lbrace\n"));
            debug_pos += sizeof ("     Token: lbrace\n");
#endif
            if (current == (struct parse_node *) NULL) {
                root = current = new;
                break;
            }
            /* Percolate upwards */
            if (current != (struct parse_node *) NULL) {
                switch (current->token.type) {
                case token_not:
                case token_eq:
                case token_ne:
                case token_and:
                case token_or:
                case token_lbrace:
                case token_ge:
                case token_gt:
                case token_le:
                case token_lt:
                    break;
                case token_string:
                case token_re:
                case token_group:
                default:
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                "Invalid expression \"%s\" in file %s",
                                expr, r->filename);
                    *was_error = 1;
                    return retval;
                }
            }
            if (current == (struct parse_node *) NULL) {
                new->left = root;
                new->left->parent = new;
                new->parent = (struct parse_node *) NULL;
                root = new;
            }
            else {
                new->left = current->right;
                current->right = new;
                new->parent = current;
            }
            current = new;
            break;
        default:
            break;
        }
    }

    /* Evaluate Parse Tree */
    current = root;
    while (current != (struct parse_node *) NULL) {
        switch (current->token.type) {
        case token_string:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate string\n",
                    sizeof ("     Evaluate string\n"));
            debug_pos += sizeof ("     Evaluate string\n");
#endif
            buffer = ap_ssi_parse_string(r, ctx, current->token.value, NULL, 
                                         MAX_STRING_LEN, 0);
            current->token.value = buffer;
            current->value = (current->token.value[0] != '\0');
            current->done = 1;
            current = current->parent;
            break;

        case token_re:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "No operator before regex of expr \"%s\" in file %s",
                          expr, r->filename);
            *was_error = 1;
            return retval;

        case token_and:
        case token_or:
#ifdef DEBUG_INCLUDE
            memcpy(&debug[debug_pos], "     Evaluate and/or\n",
                    sizeof("     Evaluate and/or\n"));
            debug_pos += sizeof("     Evaluate and/or\n");
#endif
            if (current->left  == (struct parse_node *) NULL ||
                current->right == (struct parse_node *) NULL) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression \"%s\" in file %s",
                              expr, r->filename);
                *was_error = 1;
                return retval;
            }
            if (!current->left->done) {
                switch (current->left->token.type) {
                case token_string:
                    buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                                 NULL, MAX_STRING_LEN, 0);
                    current->left->token.value = buffer;
                    current->left->value = 
                                       (current->left->token.value[0] != '\0');
                    current->left->done = 1;
                    break;
                default:
                    current = current->left;
                    continue;
                }
            }
            if (!current->right->done) {
                switch (current->right->token.type) {
                case token_string:
                    buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                                 NULL, MAX_STRING_LEN, 0);
                    current->right->token.value = buffer;
                    current->right->value = 
                                      (current->right->token.value[0] != '\0');
                    current->right->done = 1;
                    break;
                default:
                    current = current->right;
                    continue;
                }
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Left: %c\n",
                                  current->left->value ? '1' : '0');
            debug_pos += sprintf (&debug[debug_pos], "     Right: %c\n",
                                  current->right->value ? '1' : '0');
#endif
            if (current->token.type == token_and) {
                current->value = current->left->value && current->right->value;
            }
            else {
                current->value = current->left->value || current->right->value;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_eq:
        case token_ne:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate eq/ne\n",
                    sizeof ("     Evaluate eq/ne\n"));
            debug_pos += sizeof ("     Evaluate eq/ne\n");
#endif
            if ((current->left == (struct parse_node *) NULL) ||
                (current->right == (struct parse_node *) NULL) ||
                (current->left->token.type != token_string) ||
                ((current->right->token.type != token_string) &&
                 (current->right->token.type != token_re))) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->left->token.value = buffer;
            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->right->token.value = buffer;
            if (current->right->token.type == token_re) {
#ifdef DEBUG_INCLUDE
                debug_pos += sprintf (&debug[debug_pos],
                                      "     Re Compare (%s) with /%s/\n",
                                      current->left->token.value,
                                      current->right->token.value);
#endif
                current->value =
                    re_check(r, ctx, current->left->token.value,
                             current->right->token.value);
            }
            else {
#ifdef DEBUG_INCLUDE
                debug_pos += sprintf (&debug[debug_pos],
                                      "     Compare (%s) with (%s)\n",
                                      current->left->token.value,
                                      current->right->token.value);
#endif
                current->value =
                    (strcmp(current->left->token.value,
                            current->right->token.value) == 0);
            }
            if (current->token.type == token_ne) {
                current->value = !current->value;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;
        case token_ge:
        case token_gt:
        case token_le:
        case token_lt:
#ifdef DEBUG_INCLUDE
            memcpy (&debug[debug_pos], "     Evaluate ge/gt/le/lt\n",
                    sizeof ("     Evaluate ge/gt/le/lt\n"));
            debug_pos += sizeof ("     Evaluate ge/gt/le/lt\n");
#endif
            if ((current->left == (struct parse_node *) NULL) ||
                (current->right == (struct parse_node *) NULL) ||
                (current->left->token.type != token_string) ||
                (current->right->token.type != token_string)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "Invalid expression \"%s\" in file %s",
                            expr, r->filename);
                *was_error = 1;
                return retval;
            }
            buffer = ap_ssi_parse_string(r, ctx, current->left->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->left->token.value = buffer;
            buffer = ap_ssi_parse_string(r, ctx, current->right->token.value,
                                         NULL, MAX_STRING_LEN, 0);
            current->right->token.value = buffer;
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos],
                                  "     Compare (%s) with (%s)\n",
                                  current->left->token.value,
                                  current->right->token.value);
#endif
            current->value =
                strcmp(current->left->token.value,
                       current->right->token.value);
            if (current->token.type == token_ge) {
                current->value = current->value >= 0;
            }
            else if (current->token.type == token_gt) {
                current->value = current->value > 0;
            }
            else if (current->token.type == token_le) {
                current->value = current->value <= 0;
            }
            else if (current->token.type == token_lt) {
                current->value = current->value < 0;
            }
            else {
                current->value = 0;     /* Don't return -1 if unknown token */
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Returning %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_not:
            if (current->right != (struct parse_node *) NULL) {
                if (!current->right->done) {
                    current = current->right;
                    continue;
                }
                current->value = !current->right->value;
            }
            else {
                current->value = 0;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Evaluate !: %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_group:
            if (current->right != (struct parse_node *) NULL) {
                if (!current->right->done) {
                    current = current->right;
                    continue;
                }
                current->value = current->right->value;
            }
            else {
                current->value = 1;
            }
#ifdef DEBUG_INCLUDE
            debug_pos += sprintf (&debug[debug_pos], "     Evaluate (): %c\n",
                                  current->value ? '1' : '0');
#endif
            current->done = 1;
            current = current->parent;
            break;

        case token_lbrace:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Unmatched '(' in \"%s\" in file %s",
                        expr, r->filename);
            *was_error = 1;
            return retval;

        case token_rbrace:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "Unmatched ')' in \"%s\" in file %s",
                        expr, r->filename);
            *was_error = 1;
            return retval;

        default:
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "bad token type");
            *was_error = 1;
            return retval;
        }
    }

    retval = (root == (struct parse_node *) NULL) ? 0 : root->value;
    return (retval);
}