static const char *remove_extension_info(cmd_parms *cmd, void *m_,
                                         const char *ext)
{
    mime_dir_config *m = (mime_dir_config *) m_;
    attrib_info *suffix;
    if (*ext == '.') {
        ++ext;
    }
    if (!m->remove_mappings) {
        m->remove_mappings = apr_array_make(cmd->pool, 4, sizeof(*suffix));
    }
    suffix = (attrib_info *)apr_array_push(m->remove_mappings);
    suffix->name = apr_pstrdup(cmd->pool, ext);
    ap_str_tolower(suffix->name);
    suffix->offset = (int) (long) cmd->info;
    return NULL;
}