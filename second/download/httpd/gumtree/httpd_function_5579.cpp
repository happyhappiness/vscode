static const char *macro_section(cmd_parms * cmd,
                                 void *dummy, const char *arg)
{
    apr_pool_t *pool;
    char *endp, *name, *where;
    const char *errmsg;
    ap_macro_t *macro;

    debug(fprintf(stderr, "macro_section: arg='%s'\n", arg));

    /* lazy initialization */
    if (ap_macros == NULL)
        ap_macros = apr_hash_make(cmd->temp_pool);
    ap_assert(ap_macros != NULL);

    pool = apr_hash_pool_get(ap_macros);

    endp = (char *) ap_strrchr_c(arg, '>');

    if (endp == NULL) {
        return BEGIN_MACRO "> directive missing closing '>'";
    }

    if (endp == arg) {
        return BEGIN_MACRO " macro definition: empty name";
    }

    warn_if_non_blank("non blank chars found after " BEGIN_MACRO " closing '>'",
                      endp+1, cmd->config_file);

    /* coldly drop '>[^>]*$' out */
    *endp = '\0';

    /* get lowercase macro name */
    name = ap_getword_conf(pool, &arg);
    if (empty_string_p(name)) {
        return BEGIN_MACRO " macro definition: name not found";
    }

    ap_str_tolower(name);
    macro = apr_hash_get(ap_macros, name, APR_HASH_KEY_STRING);

    if (macro != NULL) {
        /* already defined: warn about the redefinition */
        ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                     "macro '%s' multiply defined: "
                     "%s, redefined on line %d of \"%s\"",
                     macro->name, macro->location,
                     cmd->config_file->line_number, cmd->config_file->name);
    }
    else {
        /* allocate a new macro */
        macro = (ap_macro_t *) apr_palloc(pool, sizeof(ap_macro_t));
        macro->name = name;
    }

    debug(fprintf(stderr, "macro_section: name=%s\n", name));

    /* get macro arguments */
    macro->location = apr_psprintf(pool,
                                   "defined on line %d of \"%s\"",
                                   cmd->config_file->line_number,
                                   cmd->config_file->name);
    debug(fprintf(stderr, "macro_section: location=%s\n", macro->location));

    where =
        apr_psprintf(pool, "macro '%s' (%s)", macro->name, macro->location);

    if (looks_like_an_argument(name)) {
        ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                     "%s better prefix a macro name with any of '%s'",
                     where, ARG_PREFIX);
    }

    /* get macro parameters */
    macro->arguments = get_arguments(pool, arg);

    errmsg = check_macro_arguments(cmd->temp_pool, macro);

    if (errmsg) {
        return errmsg;
    }

    errmsg = get_lines_till_end_token(pool, cmd->config_file,
                                      END_MACRO, BEGIN_MACRO,
                                      where, &macro->contents);

    if (errmsg) {
        return apr_psprintf(cmd->temp_pool,
                            "%s" APR_EOL_STR "\tcontents error: %s",
                            where, errmsg);
    }

    errmsg = check_macro_contents(cmd->temp_pool, macro);

    if (errmsg) {
        return apr_psprintf(cmd->temp_pool,
                            "%s" APR_EOL_STR "\tcontents checking error: %s",
                            where, errmsg);
    }

    /* store the new macro */
    apr_hash_set(ap_macros, name, APR_HASH_KEY_STRING, macro);

    return NULL;
}