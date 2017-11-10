static const char *add_ignore(cmd_parms *cmd, void *d, const char *ext)
{
    push_item(((autoindex_config_rec *) d)->ign_list, 0, ext, cmd->path, NULL);
    return NULL;
}