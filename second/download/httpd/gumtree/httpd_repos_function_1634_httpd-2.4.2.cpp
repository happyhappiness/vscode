static void *create_mime_dir_config(apr_pool_t *p, char *dummy)
{
    mime_dir_config *new = apr_palloc(p, sizeof(mime_dir_config));

    new->extension_mappings = NULL;
    new->remove_mappings = NULL;

    new->default_language = NULL;

    new->multimatch = MULTIMATCH_UNSET;

    new->use_path_info = 2;

    return new;
}