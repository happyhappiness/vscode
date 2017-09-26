        }
    }

    *p = '\0';
}

static void add_include_vars(request_rec *r, const char *timefmt)
{
    apr_table_t *e = r->subprocess_env;
    char *t;

    apr_table_setn(e, "DATE_LOCAL", LAZY_VALUE);
    apr_table_setn(e, "DATE_GMT", LAZY_VALUE);
    apr_table_setn(e, "LAST_MODIFIED", LAZY_VALUE);
    apr_table_setn(e, "DOCUMENT_URI", r->uri);
    if (r->path_info && *r->path_info) {
        apr_table_setn(e, "DOCUMENT_PATH_INFO", r->path_info);
    }
    apr_table_setn(e, "USER_NAME", LAZY_VALUE);
    if (r->filename && (t = strrchr(r->filename, '/'))) {
        apr_table_setn(e, "DOCUMENT_NAME", ++t);
    }
    else {
        apr_table_setn(e, "DOCUMENT_NAME", r->uri);
    }
    if (r->args) {
        char *arg_copy = apr_pstrdup(r->pool, r->args);

        ap_unescape_url(arg_copy);
        apr_table_setn(e, "QUERY_STRING_UNESCAPED",
                  ap_escape_shell_cmd(r->pool, arg_copy));
    }
}

static const char *add_include_vars_lazy(request_rec *r, const char *var)
{
    char *val;
    if (!strcasecmp(var, "DATE_LOCAL")) {
        include_dir_config *conf =
            (include_dir_config *)ap_get_module_config(r->per_dir_config,
                                                       &include_module);
        val = ap_ht_time(r->pool, r->request_time, conf->default_time_fmt, 0);
    }
    else if (!strcasecmp(var, "DATE_GMT")) {
        include_dir_config *conf =
            (include_dir_config *)ap_get_module_config(r->per_dir_config,
                                                       &include_module);
        val = ap_ht_time(r->pool, r->request_time, conf->default_time_fmt, 1);
    }
    else if (!strcasecmp(var, "LAST_MODIFIED")) {
        include_dir_config *conf =
            (include_dir_config *)ap_get_module_config(r->per_dir_config,
                                                       &include_module);
        val = ap_ht_time(r->pool, r->finfo.mtime, conf->default_time_fmt, 0);
    }
    else if (!strcasecmp(var, "USER_NAME")) {
        if (apr_uid_name_get(&val, r->finfo.user, r->pool) != APR_SUCCESS) {
            val = "<unknown>";
        }
    }
    else {
        val = NULL;
    }

    if (val) {
        apr_table_setn(r->subprocess_env, var, val);
    }
    return val;
}

static const char *get_include_var(const char *var, include_ctx_t *ctx)
{
    const char *val;
    request_rec *r = ctx->intern->r;

    if (apr_isdigit(*var) && !var[1]) {
        apr_size_t idx = *var - '0';
        backref_t *re = ctx->intern->re;

        /* Handle $0 .. $9 from the last regex evaluated.
         * The choice of returning NULL strings on not-found,
         * v.s. empty strings on an empty match is deliberate.
         */
        if (!re) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                "regex capture $%" APR_SIZE_T_FMT " refers to no regex in %s",
                idx, r->filename);
            return NULL;
        }
        else {
            if (re->nsub < idx || idx >= AP_MAX_REG_MATCH) {
                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                              "regex capture $%" APR_SIZE_T_FMT
                              " is out of range (last regex was: '%s') in %s",
                              idx, re->rexp, r->filename);
                return NULL;
            }

            if (re->match[idx].rm_so < 0 || re->match[idx].rm_eo < 0) {
                return NULL;
            }

            val = apr_pstrmemdup(ctx->dpool, re->source + re->match[idx].rm_so,
                                 re->match[idx].rm_eo - re->match[idx].rm_so);
        }
    }
    else {
        val = apr_table_get(r->subprocess_env, var);

        if (val == LAZY_VALUE) {
            val = add_include_vars_lazy(r, var);
        }
    }

    return val;
}

/*
 * Do variable substitution on strings
 *
 * (Note: If out==NULL, this function allocs a buffer for the resulting
 * string from ctx->pool. The return value is always the parsed string)
 */
static char *ap_ssi_parse_string(include_ctx_t *ctx, const char *in, char *out,
                                 apr_size_t length, int leave_name)
{
    request_rec *r = ctx->intern->r;
    result_item_t *result = NULL, *current = NULL;
    apr_size_t outlen = 0, inlen, span;
    char *ret = NULL, *eout = NULL;
    const char *p;

    if (out) {
        /* sanity check, out && !length is not supported */
        ap_assert(out && length);

        ret = out;
        eout = out + length - 1;
    }

    span = strcspn(in, "\\$");
    inlen = strlen(in);

    /* fast exit */
    if (inlen == span) {
        if (out) {
            apr_cpystrn(out, in, length);
        }
        else {
            ret = apr_pstrmemdup(ctx->pool, in, (length && length <= inlen)
                                                ? length - 1 : inlen);
        }

        return ret;
    }

    /* well, actually something to do */
    p = in + span;

    if (out) {
        if (span) {
            memcpy(out, in, (out+span <= eout) ? span : (eout-out));
            out += span;
        }
    }
    else {
        current = result = apr_palloc(ctx->dpool, sizeof(*result));
        current->next = NULL;
        current->string = in;
        current->len = span;
        outlen = span;
    }

    /* loop for specials */
    do {
        if ((out && out >= eout) || (length && outlen >= length)) {
            break;
        }

        /* prepare next entry */
        if (!out && current->len) {
            current->next = apr_palloc(ctx->dpool, sizeof(*current->next));
            current = current->next;
            current->next = NULL;
            current->len = 0;
        }

        /*
         * escaped character
         */
        if (*p == '\\') {
            if (out) {
                *out++ = (p[1] == '$') ? *++p : *p;
                ++p;
            }
            else {
                current->len = 1;
                current->string = (p[1] == '$') ? ++p : p;
                ++p;
                ++outlen;
            }
        }

        /*
         * variable expansion
         */
        else {       /* *p == '$' */
            const char *newp = NULL, *ep, *key = NULL;

            if (*++p == '{') {
                ep = ap_strchr_c(++p, '}');
                if (!ep) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Missing '}' on "
                                  "variable \"%s\" in %s", p, r->filename);
                    break;
                }

                if (p < ep) {
                    key = apr_pstrmemdup(ctx->dpool, p, ep - p);
                    newp = ep + 1;
                }
                p -= 2;
            }
            else {
                ep = p;
                while (*ep == '_' || apr_isalnum(*ep)) {
                    ++ep;
                }

                if (p < ep) {
                    key = apr_pstrmemdup(ctx->dpool, p, ep - p);
                    newp = ep;
                }
                --p;
            }

            /* empty name results in a copy of '$' in the output string */
            if (!key) {
                if (out) {
                    *out++ = *p++;
                }
                else {
                    current->len = 1;
                    current->string = p++;
                    ++outlen;
                }
            }
            else {
                const char *val = get_include_var(key, ctx);
                apr_size_t len = 0;

                if (val) {
                    len = strlen(val);
                }
                else if (leave_name) {
                    val = p;
                    len = ep - p;
                }

                if (val && len) {
                    if (out) {
                        memcpy(out, val, (out+len <= eout) ? len : (eout-out));
                        out += len;
                    }
                    else {
                        current->len = len;
                        current->string = val;
                        outlen += len;
                    }
                }

                p = newp;
            }
        }

        if ((out && out >= eout) || (length && outlen >= length)) {
            break;
        }

        /* check the remainder */
        if (*p && (span = strcspn(p, "\\$")) > 0) {
            if (!out && current->len) {
                current->next = apr_palloc(ctx->dpool, sizeof(*current->next));
                current = current->next;
                current->next = NULL;
            }

            if (out) {
                memcpy(out, p, (out+span <= eout) ? span : (eout-out));
                out += span;
            }
            else {
                current->len = span;
                current->string = p;
                outlen += span;
            }

            p += span;
        }
    } while (p < in+inlen);

    /* assemble result */
    if (out) {
        if (out > eout) {
            *eout = '\0';
        }
        else {
            *out = '\0';
        }
    }
    else {
        const char *ep;

        if (length && outlen > length) {
            outlen = length - 1;
        }

        ret = out = apr_palloc(ctx->pool, outlen + 1);
        ep = ret + outlen;

        do {
            if (result->len) {
                memcpy(out, result->string, (out+result->len <= ep)
                                            ? result->len : (ep-out));
                out += result->len;
            }
            result = result->next;
        } while (result && out < ep);

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
    int rc;

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
    rc = !ap_regexec(compiled, string, AP_MAX_REG_MATCH, re->match, 0);

    ap_pregfree(ctx->dpool, compiled);
    return rc;
}

static int get_ptoken(apr_pool_t *pool, const char **parse, token_t *token)
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
        token->value = apr_pstrdup(pool, "");
    }
    else {
        apr_size_t len = p - token->value - shift;
        char *c = apr_palloc(pool, len + 1);

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
    const char *error = "Invalid expression \"%s\" in file %s";
    const char *parse = expr;
    int was_unmatched = 0;
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

        was_unmatched = get_ptoken(ctx->dpool, &parse, &new->token);
        if (!parse) {
            break;
        }

        DEBUG_DUMP_UNMATCHED(ctx, was_unmatched);
        DEBUG_DUMP_TOKEN(ctx, &new->token);

        if (!current) {
            switch (new->token.type) {
            case TOKEN_STRING:
            case TOKEN_NOT:
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
 */

/*
 * Extract the next tag name and value.
 * If there are no more tags, set the tag name to NULL.
 * The tag value is html decoded if dodecode is non-zero.
 * The tag value may be NULL if there is no tag value..
 */
static void ap_ssi_get_tag_and_value(include_ctx_t *ctx, char **tag,
                                     char **tag_val, int dodecode)
{
    if (!ctx->intern->argv) {
        *tag = NULL;
        *tag_val = NULL;

        return;
    }

    *tag_val = ctx->intern->argv->value;
    *tag = ctx->intern->argv->name;

    ctx->intern->argv = ctx->intern->argv->next;

    if (dodecode && *tag_val) {
        decodehtml(*tag_val);
    }

    return;
}

static int find_file(request_rec *r, const char *directive, const char *tag,
                     char *tag_val, apr_finfo_t *finfo)
{
    char *to_send = tag_val;
    request_rec *rr = NULL;
    int ret=0;
    char *error_fmt = NULL;
    apr_status_t rv = APR_SUCCESS;

    if (!strcmp(tag, "file")) {
        char *newpath;

        /* be safe; only files in this directory or below allowed */
        rv = apr_filepath_merge(&newpath, NULL, tag_val,
                                APR_FILEPATH_NOTABOVEROOT |
                                APR_FILEPATH_SECUREROOTTEST |
                                APR_FILEPATH_NOTABSOLUTE, r->pool);

        if (rv != APR_SUCCESS) {
            error_fmt = "unable to access file \"%s\" "
                        "in parsed file %s";
        }
        else {
            /* note: it is okay to pass NULL for the "next filter" since
               we never attempt to "run" this sub request. */
            rr = ap_sub_req_lookup_file(newpath, r, NULL);

            if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
                to_send = rr->filename;
                if ((rv = apr_stat(finfo, to_send,
                    APR_FINFO_GPROT | APR_FINFO_MIN, rr->pool)) != APR_SUCCESS
                    && rv != APR_INCOMPLETE) {
                    error_fmt = "unable to get information about \"%s\" "
                        "in parsed file %s";
                }
            }
            else {
                error_fmt = "unable to lookup information about \"%s\" "
                            "in parsed file %s";
            }
        }

        if (error_fmt) {
            ret = -1;
            ap_log_rerror(APLOG_MARK, APLOG_ERR,
                          rv, r, error_fmt, to_send, r->filename);
        }

        if (rr) ap_destroy_sub_req(rr);

        return ret;
    }
    else if (!strcmp(tag, "virtual")) {
        /* note: it is okay to pass NULL for the "next filter" since
           we never attempt to "run" this sub request. */
        rr = ap_sub_req_lookup_uri(tag_val, r, NULL);

        if (rr->status == HTTP_OK && rr->finfo.filetype != 0) {
            memcpy((char *) finfo, (const char *) &rr->finfo,
                   sizeof(rr->finfo));
            ap_destroy_sub_req(rr);
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unable to get "
                          "information about \"%s\" in parsed file %s",
                          tag_val, r->filename);
            ap_destroy_sub_req(rr);
            return -1;
        }
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
                      "to tag %s in %s", tag, directive, r->filename);
        return -1;
    }
}

/*
 * <!--#include virtual|file="..." [virtual|file="..."] ... -->
 */
static apr_status_t handle_include(include_ctx_t *ctx, ap_filter_t *f,
                                   apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for include element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;
        request_rec *rr = NULL;
        char *error_fmt = NULL;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        if (strcmp(tag, "virtual") && strcmp(tag, "file")) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag include in %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);
        if (tag[0] == 'f') {
            char *newpath;
            apr_status_t rv;

            /* be safe; only files in this directory or below allowed */
            rv = apr_filepath_merge(&newpath, NULL, parsed_string,
                                    APR_FILEPATH_NOTABOVEROOT |
                                    APR_FILEPATH_SECUREROOTTEST |
                                    APR_FILEPATH_NOTABSOLUTE, ctx->dpool);

            if (rv != APR_SUCCESS) {
                error_fmt = "unable to include file \"%s\" in parsed file %s";
            }
            else {
                rr = ap_sub_req_lookup_file(newpath, r, f->next);
            }
        }
        else {
            rr = ap_sub_req_lookup_uri(parsed_string, r, f->next);
        }

        if (!error_fmt && rr->status != HTTP_OK) {
            error_fmt = "unable to include \"%s\" in parsed file %s";
        }

        if (!error_fmt && (ctx->flags & SSI_FLAG_NO_EXEC) &&
            rr->content_type && strncmp(rr->content_type, "text/", 5)) {

            error_fmt = "unable to include potential exec \"%s\" in parsed "
                        "file %s";
        }

        /* See the Kludge in includes_filter for why.
         * Basically, it puts a bread crumb in here, then looks
         * for the crumb later to see if its been here.
         */
        if (rr) {
            ap_set_module_config(rr->request_config, &include_module, r);
        }

        if (!error_fmt && ap_run_sub_req(rr)) {
            error_fmt = "unable to include \"%s\" in parsed file %s";
        }

        if (error_fmt) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, error_fmt, tag_val,
                          r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        }

        /* Do *not* destroy the subrequest here; it may have allocated
         * variables in this r->subprocess_env in the subrequest's
         * r->pool, so that pool must survive as long as this request.
         * Yes, this is a memory leak. */

        if (error_fmt) {
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#echo [encoding="..."] var="..." [encoding="..."] var="..." ... -->
 */
static apr_status_t handle_echo(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    enum {E_NONE, E_URL, E_ENTITY} encode;
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for echo element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    encode = E_ENTITY;

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            const char *val;
            const char *echo_text = NULL;
            apr_size_t e_len;

            val = get_include_var(ap_ssi_parse_string(ctx, tag_val, NULL,
                                                      0, SSI_EXPAND_DROP_NAME),
                                  ctx);

            if (val) {
                switch(encode) {
                case E_NONE:
                    echo_text = val;
                    break;
                case E_URL:
                    echo_text = ap_escape_uri(ctx->dpool, val);
                    break;
                case E_ENTITY:
                    echo_text = ap_escape_html(ctx->dpool, val);
                    break;
                }

                e_len = strlen(echo_text);
            }
            else {
                echo_text = ctx->intern->undefined_echo;
                e_len = ctx->intern->undefined_echo_len;
            }

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(
                                    apr_pmemdup(ctx->pool, echo_text, e_len),
                                    e_len, ctx->pool, f->c->bucket_alloc));
        }
        else if (!strcmp(tag, "encoding")) {
            if (!strcasecmp(tag_val, "none")) {
                encode = E_NONE;
            }
            else if (!strcasecmp(tag_val, "url")) {
                encode = E_URL;
            }
            else if (!strcasecmp(tag_val, "entity")) {
                encode = E_ENTITY;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"encoding\" of tag echo in "
                              "%s", tag_val, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" in tag echo of %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#config [timefmt="..."] [sizefmt="..."] [errmsg="..."]
 *             [echomsg="..."] -->
 */
static apr_status_t handle_config(include_ctx_t *ctx, ap_filter_t *f,
                                  apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    apr_table_t *env = r->subprocess_env;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for config element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_RAW);
        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "errmsg")) {
            ctx->error_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                 SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "echomsg")) {
            ctx->intern->undefined_echo =
                ap_ssi_parse_string(ctx, tag_val, NULL, 0,SSI_EXPAND_DROP_NAME);
            ctx->intern->undefined_echo_len=strlen(ctx->intern->undefined_echo);
        }
        else if (!strcmp(tag, "timefmt")) {
            apr_time_t date = r->request_time;

            ctx->time_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);

            apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date,
                           ctx->time_str, 0));
            apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date,
                           ctx->time_str, 1));
            apr_table_setn(env, "LAST_MODIFIED",
                           ap_ht_time(r->pool, r->finfo.mtime,
                           ctx->time_str, 0));
        }
        else if (!strcmp(tag, "sizefmt")) {
            char *parsed_string;

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);
            if (!strcmp(parsed_string, "bytes")) {
                ctx->flags |= SSI_FLAG_SIZE_IN_BYTES;
            }
            else if (!strcmp(parsed_string, "abbrev")) {
                ctx->flags &= SSI_FLAG_SIZE_ABBREV;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"sizefmt\" of tag config "
                              "in %s", parsed_string, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag config in %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#fsize virtual|file="..." [virtual|file="..."] ... -->
 */
static apr_status_t handle_fsize(include_ctx_t *ctx, ap_filter_t *f,
                                 apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for fsize element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;
        apr_finfo_t finfo;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);

        if (!find_file(r, "fsize", tag, parsed_string, &finfo)) {
            char *buf;
            apr_size_t len;

            if (!(ctx->flags & SSI_FLAG_SIZE_IN_BYTES)) {
                buf = apr_strfsize(finfo.size, apr_palloc(ctx->pool, 5));
                len = 4; /* omit the \0 terminator */
            }
            else {
                apr_size_t l, x, pos;
                char *tmp;

                tmp = apr_psprintf(ctx->dpool, "%" APR_OFF_T_FMT, finfo.size);
                len = l = strlen(tmp);

                for (x = 0; x < l; ++x) {
                    if (x && !((l - x) % 3)) {
                        ++len;
                    }
                }

                if (len == l) {
                    buf = apr_pstrmemdup(ctx->pool, tmp, len);
                }
                else {
                    buf = apr_palloc(ctx->pool, len);

                    for (pos = x = 0; x < l; ++x) {
                        if (x && !((l - x) % 3)) {
                            buf[pos++] = ',';
                        }
                        buf[pos++] = tmp[x];
                    }
                }
            }

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(buf, len,
                                    ctx->pool, f->c->bucket_alloc));
        }
        else {
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#flastmod virtual|file="..." [virtual|file="..."] ... -->
 */
static apr_status_t handle_flastmod(include_ctx_t *ctx, ap_filter_t *f,
                                    apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for flastmod element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;
        apr_finfo_t  finfo;
        char *parsed_string;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);
        if (!tag || !tag_val) {
            break;
        }

        parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                            SSI_EXPAND_DROP_NAME);

        if (!find_file(r, "flastmod", tag, parsed_string, &finfo)) {
            char *t_val;
            apr_size_t t_len;

            t_val = ap_ht_time(ctx->pool, finfo.mtime, ctx->time_str, 0);
            t_len = strlen(t_val);

            APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(t_val, t_len,
                                    ctx->pool, f->c->bucket_alloc));
        }
        else {
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#if expr="..." -->
 */
static apr_status_t handle_if(include_ctx_t *ctx, ap_filter_t *f,
                              apr_bucket_brigade *bb)
{
    char *tag = NULL;
    char *expr = NULL;
    request_rec *r = f->r;
    int expr_ret, was_error;

    if (ctx->argc != 1) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, (ctx->argc)
                                ? "too many arguments for if element in %s"
                                : "missing expr argument for if element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        ++(ctx->if_nesting_level);
        return APR_SUCCESS;
    }

    if (ctx->argc != 1) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);

    if (strcmp(tag, "expr")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
                      "to tag if in %s", tag, r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (!expr) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr value for if "
                      "element in %s", r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_PRINTF((ctx, "****    if expr=\"%s\"\n", expr));

    expr_ret = parse_expr(ctx, expr, &was_error);

    if (was_error) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (expr_ret) {
        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
    }
    else {
        ctx->flags &= SSI_FLAG_CLEAR_PRINT_COND;
    }

    DEBUG_DUMP_COND(ctx, "   if");

    ctx->if_nesting_level = 0;

    return APR_SUCCESS;
}

/*
 * <!--#elif expr="..." -->
 */
static apr_status_t handle_elif(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    char *tag = NULL;
    char *expr = NULL;
    request_rec *r = f->r;
    int expr_ret, was_error;

    if (ctx->argc != 1) {
        ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, (ctx->argc)
                                ? "too many arguments for if element in %s"
                                : "missing expr argument for if element in %s",
                      r->filename);
    }

    if (ctx->if_nesting_level) {
        return APR_SUCCESS;
    }

    if (ctx->argc != 1) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    ap_ssi_get_tag_and_value(ctx, &tag, &expr, SSI_VALUE_RAW);

    if (strcmp(tag, "expr")) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter \"%s\" "
                      "to tag if in %s", tag, r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (!expr) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "missing expr in elif "
                      "statement: %s", r->filename);
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_PRINTF((ctx, "****  elif expr=\"%s\"\n", expr));
    DEBUG_DUMP_COND(ctx, " elif");

    if (ctx->flags & SSI_FLAG_COND_TRUE) {
        ctx->flags &= SSI_FLAG_CLEAR_PRINTING;
        return APR_SUCCESS;
    }

    expr_ret = parse_expr(ctx, expr, &was_error);

    if (was_error) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    if (expr_ret) {
        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
    }
    else {
        ctx->flags &= SSI_FLAG_CLEAR_PRINT_COND;
    }

    DEBUG_DUMP_COND(ctx, " elif");

    return APR_SUCCESS;
}

/*
 * <!--#else -->
 */
static apr_status_t handle_else(include_ctx_t *ctx, ap_filter_t *f,
                                apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, "else directive does not take tags in %s",
                      r->filename);
    }

    if (ctx->if_nesting_level) {
        return APR_SUCCESS;
    }

    if (ctx->argc) {
        if (ctx->flags & SSI_FLAG_PRINTING) {
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        }

        return APR_SUCCESS;
    }

    DEBUG_DUMP_COND(ctx, " else");

    if (ctx->flags & SSI_FLAG_COND_TRUE) {
        ctx->flags &= SSI_FLAG_CLEAR_PRINTING;
    }
    else {
        ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);
    }

    return APR_SUCCESS;
}

/*
 * <!--#endif -->
 */
static apr_status_t handle_endif(include_ctx_t *ctx, ap_filter_t *f,
                                 apr_bucket_brigade *bb)
{
    request_rec *r = f->r;

    if (ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (!(ctx->if_nesting_level)) ? APLOG_ERR : APLOG_WARNING,
                      0, r, "endif directive does not take tags in %s",
                      r->filename);
    }

    if (ctx->if_nesting_level) {
        --(ctx->if_nesting_level);
        return APR_SUCCESS;
    }

    if (ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    DEBUG_DUMP_COND(ctx, "endif");

    ctx->flags |= (SSI_FLAG_PRINTING | SSI_FLAG_COND_TRUE);

    return APR_SUCCESS;
}

/*
 * <!--#set var="..." value="..." ... -->
 */
static apr_status_t handle_set(include_ctx_t *ctx, ap_filter_t *f,
                               apr_bucket_brigade *bb)
{
    char *var = NULL;
    request_rec *r = f->r;
    request_rec *sub = r->main;
    apr_pool_t *p = r->pool;

    if (ctx->argc < 2) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for set element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (ctx->argc < 2) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    /* we need to use the 'main' request pool to set notes as that is
     * a notes lifetime
     */
    while (sub) {
        p = sub->pool;
        sub = sub->main;
    }

    while (1) {
        char *tag = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_DECODED);

        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "var")) {
            var = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                      SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "value")) {
            char *parsed_string;

            if (!var) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "variable must "
                              "precede value in set directive in %s",
                              r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);
            apr_table_setn(r->subprocess_env, apr_pstrdup(p, var),
                           apr_pstrdup(p, parsed_string));
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "Invalid tag for set "
                          "directive in %s", r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}

/*
 * <!--#printenv -->
 */
static apr_status_t handle_printenv(include_ctx_t *ctx, ap_filter_t *f,
                                    apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    int i;

    if (ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "printenv directive does not take tags in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    arr = apr_table_elts(r->subprocess_env);
    elts = (apr_table_entry_t *)arr->elts;

    for (i = 0; i < arr->nelts; ++i) {
        const char *key_text, *val_text;
        char *key_val, *next;
        apr_size_t k_len, v_len, kv_length;

        /* get key */
        key_text = ap_escape_html(ctx->dpool, elts[i].key);
        k_len = strlen(key_text);

        /* get value */
        val_text = elts[i].val;
        if (val_text == LAZY_VALUE) {
            val_text = add_include_vars_lazy(r, elts[i].key);
        }
        val_text = ap_escape_html(ctx->dpool, elts[i].val);
        v_len = strlen(val_text);

        /* assemble result */
        kv_length = k_len + v_len + sizeof("=\n");
        key_val = apr_palloc(ctx->pool, kv_length);
        next = key_val;

        memcpy(next, key_text, k_len);
        next += k_len;
        *next++ = '=';
        memcpy(next, val_text, v_len);
        next += v_len;
        *next++ = '\n';
        *next = 0;

        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(key_val, kv_length-1,
                                ctx->pool, f->c->bucket_alloc));
    }

    ctx->flush_now = 1;
    return APR_SUCCESS;
}


/*
 * +-------------------------------------------------------+
 * |                                                       |
 * |               Main Includes-Filter Engine
 * |                                                       |
 * +-------------------------------------------------------+
 */

/* This is an implementation of the BNDM search algorithm.
 *
 * Fast and Flexible String Matching by Combining Bit-parallelism and
 * Suffix Automata (2001)
 * Gonzalo Navarro, Mathieu Raffinot
 *
 * http://www-igm.univ-mlv.fr/~raffinot/ftp/jea2001.ps.gz
 *
 * Initial code submitted by Sascha Schumann.
 */

/* Precompile the bndm_t data structure. */
static bndm_t *bndm_compile(apr_pool_t *pool, const char *n, apr_size_t nl)
{
    unsigned int x;
    const char *ne = n + nl;
    bndm_t *t = apr_palloc(pool, sizeof(*t));

    memset(t->T, 0, sizeof(unsigned int) * 256);
    t->pattern_len = nl;

    for (x = 1; n < ne; x <<= 1) {
        t->T[(unsigned char) *n++] |= x;
    }

    t->x = x - 1;

    return t;
}

/* Implements the BNDM search algorithm (as described above).
 *
 * h  - the string to look in
 * hl - length of the string to look for
 * t  - precompiled bndm structure against the pattern
 *
 * Returns the count of character that is the first match or hl if no
 * match is found.
 */
static apr_size_t bndm(bndm_t *t, const char *h, apr_size_t hl)
{
    const char *skip;
    const char *he, *p, *pi;
    unsigned int *T, x, d;
    apr_size_t nl;

    he = h + hl;

    T = t->T;
    x = t->x;
    nl = t->pattern_len;

    pi = h - 1; /* pi: p initial */
    p = pi + nl; /* compare window right to left. point to the first char */

    while (p < he) {
        skip = p;
        d = x;
        do {
            d &= T[(unsigned char) *p--];
            if (!d) {
                break;
            }
            if ((d & 1)) {
                if (p != pi) {
                    skip = p;
                }
                else {
                    return p - h + 1;
                }
            }
            d >>= 1;
        } while (d);

        pi = skip;
        p = pi + nl;
    }

    return hl;
}

/*
 * returns the index position of the first byte of start_seq (or the len of
 * the buffer as non-match)
 */
static apr_size_t find_start_sequence(include_ctx_t *ctx, const char *data,
                                      apr_size_t len)
{
    struct ssi_internal_ctx *intern = ctx->intern;
    apr_size_t slen = intern->start_seq_pat->pattern_len;
    apr_size_t index;
    const char *p, *ep;

    if (len < slen) {
        p = data; /* try partial match at the end of the buffer (below) */
    }
    else {
        /* try fast bndm search over the buffer
         * (hopefully the whole start sequence can be found in this buffer)
         */
        index = bndm(intern->start_seq_pat, data, len);

        /* wow, found it. ready. */
        if (index < len) {
            intern->state = PARSE_DIRECTIVE;
            return index;
        }
        else {
            /* ok, the pattern can't be found as whole in the buffer,
             * check the end for a partial match
             */
            p = data + len - slen + 1;
        }
    }

    ep = data + len;
    do {
        while (p < ep && *p != *intern->start_seq) {
            ++p;
        }

        index = p - data;

        /* found a possible start_seq start */
        if (p < ep) {
            apr_size_t pos = 1;

            ++p;
            while (p < ep && *p == intern->start_seq[pos]) {
                ++p;
                ++pos;
            }

            /* partial match found. Store the info for the next round */
            if (p == ep) {
                intern->state = PARSE_HEAD;
                intern->parse_pos = pos;
                return index;
            }
        }

        /* we must try all combinations; consider (e.g.) SSIStartTag "--->"
         * and a string data of "--.-" and the end of the buffer
