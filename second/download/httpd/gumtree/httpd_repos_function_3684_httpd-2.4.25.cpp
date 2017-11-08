static const char *fcgi_authz_parse(cmd_parms *cmd, const char *require_line,
                                    const void **parsed_require_line)
{
    /* Allowed form: Require [not] registered-provider-name<EOS>
     */
    if (strcmp(require_line, "")) {
        return "mod_authnz_fcgi doesn't support restrictions on providers "
               "(i.e., multiple require args)";
    }

    return NULL;
}