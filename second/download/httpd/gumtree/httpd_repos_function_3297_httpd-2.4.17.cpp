static const char *fcgi_check_authn_provider(cmd_parms *cmd,
                                        void *d,
                                        int argc,
                                        char *const argv[])
{
    const char *dname = "AuthnzFcgiCheckAuthnProvider";
    fcgi_dir_conf *dc = d;
    int ca = 0;

    if (ca >= argc) {
        return apr_pstrcat(cmd->pool, dname, ": No provider given", NULL);
    }

    dc->name = argv[ca];
    ca++;

    if (!strcasecmp(dc->name, "None")) {
        if (ca < argc) {
            return "Options aren't supported with \"None\"";
        }
    }

    while (ca < argc) {
        const char *var = argv[ca], *val;
        int badarg = 0;

        ca++;

        /* at present, everything needs an argument */
        if (ca >= argc) {
            return apr_pstrcat(cmd->pool, dname, ": ", var,
                               "needs an argument", NULL);
        }

        val = argv[ca];
        ca++;

        if (!strcasecmp(var, "Authoritative")) {
            if (!strcasecmp(val, "On")) {
                dc->authoritative = 1;
            }
            else if (!strcasecmp(val, "Off")) {
                dc->authoritative = 0;
            }
            else {
                badarg = 1;
            }
        }
        else if (!strcasecmp(var, "DefaultUser")) {
            dc->default_user = val;
        }
        else if (!strcasecmp(var, "RequireBasicAuth")) {
            if (!strcasecmp(val, "On")) {
                dc->require_basic_auth = 1;
            }
            else if (!strcasecmp(val, "Off")) {
                dc->require_basic_auth = 0;
            }
            else {
                badarg = 1;
            }
        }
        else if (!strcasecmp(var, "UserExpr")) {
            const char *err;
            int flags = AP_EXPR_FLAG_DONT_VARY | AP_EXPR_FLAG_RESTRICTED
                | AP_EXPR_FLAG_STRING_RESULT;

            dc->user_expr = ap_expr_parse_cmd(cmd, val,
                                              flags, &err, NULL);
            if (err) {
                return apr_psprintf(cmd->pool, "%s: Error parsing '%s': '%s'",
                                    dname, val, err);
            }
        }
        else {
            return apr_pstrcat(cmd->pool, dname, ": Unexpected option '",
                               var, "'", NULL);
        }
        if (badarg) {
            return apr_pstrcat(cmd->pool, dname, ": Bad argument '",
                               val, "' to option '", var, "'", NULL);
        }
    }

    return NULL;
}