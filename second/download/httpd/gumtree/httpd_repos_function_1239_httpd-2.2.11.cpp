static const char *add_header(cmd_parms *cmd, void *d, const char *name)
{
    push_item(((autoindex_config_rec *) d)->hdr_list, 0, NULL, cmd->path,
              name);
    return NULL;
}