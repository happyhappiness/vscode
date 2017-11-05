static int expr_eval(request_rec *r, ap_parse_node_t *root,
                     int *was_error, backref_t **reptr,
                     string_func_t string_func, opt_func_t eval_func)
{
    ap_parse_node_t *current = root;
    const char *error = NULL;
    unsigned int regex = 0;
    const char *val;
    const char *lval;
    const char *rval;

    /* Evaluate Parse Tree */
    while (current) {
        switch (current->token.type) {
        case TOKEN_STRING:
            val = PARSE_STRING(r, current->token.value);
            current->value = !!*val;
            break;

        case TOKEN_AND:
        case TOKEN_OR:
            if (!current->left || !current->right) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid expression in file %s", r->filename);
                *was_error = 1;
                return 0;
            }

            if (!current->left->done) {
                switch (current->left->token.type) {
                case TOKEN_STRING:
                    lval = PARSE_STRING(r, current->left->token.value);
                    current->left->value = !!*lval;
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
                        rval = PARSE_STRING(r,current->right->token.value);
                        current->right->value = !!*rval;
                        DEBUG_DUMP_EVAL(r, current->right);
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
                            "Invalid expression in file %s", r->filename);
                *was_error = 1;
                return 0;
            }
            lval = PARSE_STRING(r, current->left->token.value);
            rval = PARSE_STRING(r, current->right->token.value);

            if (current->right->token.type == TOKEN_RE) {
                current->value = re_check(r, lval, rval, reptr);
                --regex;
            }
            else {
                current->value = !strcmp(lval, rval);
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
                              "Invalid expression in file %s", r->filename);
                *was_error = 1;
                return 0;
            }

            lval = PARSE_STRING(r, current->left->token.value);
            rval = PARSE_STRING(r, current->right->token.value);

            current->value = strcmp(lval, rval);

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
            if (eval_func) {
                *was_error = eval_func(r, current, string_func);
                if (*was_error) {
                    return 0;
                }
            }
            break;

        case TOKEN_RE:
            if (!error) {
                error = "No operator before regex in file %s";
            }
        case TOKEN_LBRACE:
            if (!error) {
                error = "Unmatched '(' in file %s";
            }
        default:
            if (!error) {
                error = "internal parser error in file %s";
            }

            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error, r->filename);
            *was_error = 1;
            return 0;
        }

        DEBUG_DUMP_EVAL(r, current);
        current->done = 1;
        current = current->parent;
    }

    return (root ? root->value : 0);
}