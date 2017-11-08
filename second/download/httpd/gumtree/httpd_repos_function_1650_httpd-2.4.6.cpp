static const char *undef_macro(cmd_parms * cmd, void *dummy, const char *arg)
{
    char *name;
    ap_macro_t *macro;

    /* must be initialized, or no macros has been defined */
    if (ap_macros == NULL) {
        return "no macro defined before " UNDEF_MACRO;
    }

    if (empty_string_p(arg)) {
        return "no macro name specified with " UNDEF_MACRO;
    }

    /* check that the macro is defined */
    name = apr_pstrdup(cmd->temp_pool, arg);
    ap_str_tolower(name);
    macro = apr_hash_get(ap_macros, name, APR_HASH_KEY_STRING);
    if (macro == NULL) {
        /* could be a warning? */
        return apr_psprintf(cmd->temp_pool,
                            "cannot remove undefined macro '%s'", name);
    }

    /* free macro: cannot do that */
    /* remove macro from hash table */
    apr_hash_set(ap_macros, name, APR_HASH_KEY_STRING, NULL);

    return NULL;
}