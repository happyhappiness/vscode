
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
