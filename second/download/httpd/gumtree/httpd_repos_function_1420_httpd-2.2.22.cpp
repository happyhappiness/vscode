static void *merge_mime_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    mime_dir_config *base = (mime_dir_config *)basev;
    mime_dir_config *add = (mime_dir_config *)addv;
    mime_dir_config *new = apr_palloc(p, sizeof(mime_dir_config));

    if (base->extension_mappings && add->extension_mappings) {
        new->extension_mappings = apr_hash_merge(p, add->extension_mappings,
                                                 base->extension_mappings,
                                                 overlay_extension_mappings,
                                                 NULL);
    }
    else {
        if (base->extension_mappings == NULL) {
            new->extension_mappings = add->extension_mappings;
        }
        else {
            new->extension_mappings = base->extension_mappings;
        }
        /* We may not be merging the tables, but if we potentially will change
         * an exinfo member, then we are about to trounce it anyways.
         * We must have a copy for safety.
         */
        if (new->extension_mappings && add->remove_mappings) {
            new->extension_mappings =
                apr_hash_copy(p, new->extension_mappings);
        }
    }

    if (new->extension_mappings) {
        if (add->remove_mappings)
            remove_items(p, add->remove_mappings, new->extension_mappings);
    }
    new->remove_mappings = NULL;

    new->default_language = add->default_language ?
        add->default_language : base->default_language;

    new->multimatch = (add->multimatch != MULTIMATCH_UNSET) ?
        add->multimatch : base->multimatch;

    if ((add->use_path_info & 2) == 0) {
        new->use_path_info = add->use_path_info;
    }
    else {
        new->use_path_info = base->use_path_info;
    }

    return new;
}