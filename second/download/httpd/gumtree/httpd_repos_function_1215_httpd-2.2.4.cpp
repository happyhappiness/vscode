static const char *add_alt(cmd_parms *cmd, void *d, const char *alt,
                           const char *to)
{
    if (cmd->info == BY_PATH) {
        if (!strcmp(to, "**DIRECTORY**")) {
            to = "^^DIRECTORY^^";
        }
    }
    if (cmd->info == BY_ENCODING) {
        char *tmp = apr_pstrdup(cmd->pool, to);
        ap_str_tolower(tmp);
        to = tmp;
    }

    push_item(((autoindex_config_rec *) d)->alt_list, cmd->info, to,
              cmd->path, alt);
    return NULL;
}