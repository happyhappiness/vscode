static const char *set_default_end_tag(cmd_parms *cmd, void *mconfig,
                                       const char *tag)
{
    include_server_config *conf;
    const char *p = tag;

    /* sanity check. The parser may fail otherwise */
    while (*p) {
        if (apr_isspace(*p)) {
            return "SSIEndTag may not contain any whitespaces";
        }
        ++p;
    }

    conf= ap_get_module_config(cmd->server->module_config , &include_module);
    conf->default_end_tag = tag;

    return NULL;
}