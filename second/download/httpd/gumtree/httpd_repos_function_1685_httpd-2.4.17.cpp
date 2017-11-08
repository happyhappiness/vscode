static const char *use_macro(cmd_parms * cmd, void *dummy, const char *arg)
{
    char *name, *recursion, *where;
    const char *errmsg;
    ap_macro_t *macro;
    apr_array_header_t *replacements;
    apr_array_header_t *contents;

    debug(fprintf(stderr, "use_macro -%s-\n", arg));

    /* must be initialized, or no macros has been defined */
    if (ap_macros == NULL) {
        return "no macro defined before " USE_MACRO;
    }

    /* get lowercase macro name */
    name = ap_getword_conf(cmd->temp_pool, &arg);
    ap_str_tolower(name);

    if (empty_string_p(name)) {
        return "no macro name specified with " USE_MACRO;
    }

    /* get macro definition */
    macro = apr_hash_get(ap_macros, name, APR_HASH_KEY_STRING);

    if (!macro) {
        return apr_psprintf(cmd->temp_pool, "macro '%s' undefined", name);
    }

    /* recursion is detected here by looking at the config file name,
     * which may already contains "macro 'foo'". Ok, it looks like a hack,
     * but otherwise it is uneasy to keep this data available somewhere...
     * the name has just the needed visibility and liveness.
     */
    recursion =
        apr_pstrcat(cmd->temp_pool, "macro '", macro->name, "'", NULL);

    if (ap_strstr((char *) cmd->config_file->name, recursion)) {
        return apr_psprintf(cmd->temp_pool,
                            "recursive use of macro '%s' is invalid",
                            macro->name);
    }

    /* get macro arguments */
    replacements = get_arguments(cmd->temp_pool, arg);

    if (macro->arguments->nelts != replacements->nelts) {
        return apr_psprintf(cmd->temp_pool,
                            "macro '%s' (%s) used "
                            "with %d arguments instead of %d",
                            macro->name, macro->location,
                            replacements->nelts, macro->arguments->nelts);
    }

    where = apr_psprintf(cmd->temp_pool,
                         "macro '%s' (%s) used on line %d of \"%s\"",
                         macro->name, macro->location,
                         cmd->config_file->line_number,
                         cmd->config_file->name);

    check_macro_use_arguments(where, replacements);

    errmsg = process_content(cmd->temp_pool, macro, replacements,
                             NULL, &contents);

    if (errmsg) {
        return apr_psprintf(cmd->temp_pool,
                            "%s error while substituting: %s",
                            where, errmsg);
    }

    /* the current "config file" is replaced by a string array...
       at the end of processing the array, the initial config file
       will be returned there (see next_one) so as to go on. */
    cmd->config_file = make_array_config(cmd->temp_pool, contents, where,
                                         cmd->config_file, &cmd->config_file);

    return NULL;
}