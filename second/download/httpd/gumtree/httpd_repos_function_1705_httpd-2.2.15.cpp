static const char *set_default_start_tag(cmd_parms *cmd, void *mconfig,
                                         const char *tag)
{
    include_server_config *conf;
    const char *p = tag;

    /* be consistent. (See below in set_default_end_tag) */
    while (*p) {
        if (apr_isspace(*p)) {
            return "SSIStartTag may not contain any whitespaces";
        }
        ++p;
    }

    conf= ap_get_module_config(cmd->server->module_config , &include_module);
    conf->default_start_tag = tag;

    return NULL;
}