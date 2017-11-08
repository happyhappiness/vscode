static const char *add_icon(cmd_parms *cmd, void *d, const char *icon,
                            const char *to)
{
    char *iconbak = apr_pstrdup(cmd->pool, icon);

    if (icon[0] == '(') {
        char *alt;
        char *cl = strchr(iconbak, ')');

        if (cl == NULL) {
            return "missing closing paren";
        }
        alt = ap_getword_nc(cmd->pool, &iconbak, ',');
        *cl = '\0';                             /* Lose closing paren */
        add_alt(cmd, d, &alt[1], to);
    }
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

    push_item(((autoindex_config_rec *) d)->icon_list, cmd->info, to,
              cmd->path, iconbak);
    return NULL;
}