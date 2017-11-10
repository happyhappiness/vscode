static const char *add_extension_info(cmd_parms *cmd, void *m_,
                                      const char *value_, const char* ext)
{
    mime_dir_config *m=m_;
    extension_info *exinfo;
    int offset = (int) (long) cmd->info;
    char *key = apr_pstrdup(cmd->temp_pool, ext);
    char *value = apr_pstrdup(cmd->pool, value_);
    ap_str_tolower(value);
    ap_str_tolower(key);

    if (*key == '.') {
        ++key;
    }
    if (!m->extension_mappings) {
        m->extension_mappings = apr_hash_make(cmd->pool);
        exinfo = NULL;
    }
    else {
        exinfo = (extension_info*)apr_hash_get(m->extension_mappings, key,
                                               APR_HASH_KEY_STRING);
    }
    if (!exinfo) {
        exinfo = apr_pcalloc(cmd->pool, sizeof(extension_info));
        key = apr_pstrdup(cmd->pool, key);
        apr_hash_set(m->extension_mappings, key, APR_HASH_KEY_STRING, exinfo);
    }
    *(const char**)((char *)exinfo + offset) = value;
    return NULL;
}