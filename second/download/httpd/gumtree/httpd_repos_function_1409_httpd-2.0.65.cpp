static const char *set_extension_map(cmd_parms *cmd, netware_dir_config *m,
                                     char *CGIhdlr, char *ext, char *detach)
{
    int i, len;

    if (*ext == '.')
        ++ext;
  
    if (CGIhdlr != NULL) {
        len = strlen(CGIhdlr);    
        for (i=0; i<len; i++) {
            if (CGIhdlr[i] == '\\') {
                CGIhdlr[i] = '/';
            }
        }
    }

    apr_table_set(m->file_type_handlers, ext, CGIhdlr);
    if (detach) {
        apr_table_set(m->file_handler_mode, ext, "y");
    }

    return NULL;
}