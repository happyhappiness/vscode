static const char *set_extension_map(cmd_parms *cmd, netware_dir_config *m,
                                     char *CGIhdlr, char *ext, char *detach)
{
    if (*ext == '.')
        ++ext;
    apr_table_set(m->file_type_handlers, ext, CGIhdlr);
    if (detach) {
        apr_table_set(m->file_handler_mode, ext, "y");
    }
    return NULL;
}