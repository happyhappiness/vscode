static const char *add_readme(cmd_parms *cmd, void *d, const char *name)
{
    push_item(((autoindex_config_rec *) d)->rdme_list, 0, NULL, cmd->path,
              name);
    return NULL;
}