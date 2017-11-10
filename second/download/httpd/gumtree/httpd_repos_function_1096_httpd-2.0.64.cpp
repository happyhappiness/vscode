static const char *add_desc(cmd_parms *cmd, void *d, const char *desc,
                            const char *to)
{
    autoindex_config_rec *dcfg = (autoindex_config_rec *) d;
    ai_desc_t *desc_entry;
    char *prefix = "";

    desc_entry = (ai_desc_t *) apr_array_push(dcfg->desc_list);
    desc_entry->full_path = (ap_strchr_c(to, '/') == NULL) ? 0 : 1;
    desc_entry->wildcards = (WILDCARDS_REQUIRED
                             || desc_entry->full_path
                             || apr_fnmatch_test(to));
    if (desc_entry->wildcards) {
        prefix = desc_entry->full_path ? "*/" : "*";
        desc_entry->pattern = apr_pstrcat(dcfg->desc_list->pool,
                                          prefix, to, "*", NULL);
    }
    else {
        desc_entry->pattern = apr_pstrdup(dcfg->desc_list->pool, to);
    }
    desc_entry->description = apr_pstrdup(dcfg->desc_list->pool, desc);
    return NULL;
}