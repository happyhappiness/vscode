static const char *authz_merge_sections(cmd_parms *cmd, void *mconfig,
                                        const char *arg)
{
    authz_core_dir_conf *conf = mconfig;

    if (!strcasecmp(arg, "Off")) {
        conf->op = AUTHZ_LOGIC_OFF;
    }
    else if (!strcasecmp(arg, "And")) {
        conf->op = AUTHZ_LOGIC_AND;
    }
    else if (!strcasecmp(arg, "Or")) {
        conf->op = AUTHZ_LOGIC_OR;
    }
    else {
        return apr_pstrcat(cmd->pool, cmd->cmd->name, " must be one of: "
                           "Off | And | Or", NULL);
    }

    return NULL;
}