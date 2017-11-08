static void *create_autoindex_config(apr_pool_t *p, char *dummy)
{
    autoindex_config_rec *new =
    (autoindex_config_rec *) apr_pcalloc(p, sizeof(autoindex_config_rec));

    new->icon_width = 0;
    new->icon_height = 0;
    new->name_width = DEFAULT_NAME_WIDTH;
    new->name_adjust = K_UNSET;
    new->desc_width = DEFAULT_DESC_WIDTH; 
    new->desc_adjust = K_UNSET; 
    new->icon_list = apr_array_make(p, 4, sizeof(struct item));
    new->alt_list = apr_array_make(p, 4, sizeof(struct item));
    new->desc_list = apr_array_make(p, 4, sizeof(ai_desc_t));
    new->ign_list = apr_array_make(p, 4, sizeof(struct item));
    new->hdr_list = apr_array_make(p, 4, sizeof(struct item));
    new->rdme_list = apr_array_make(p, 4, sizeof(struct item));
    new->opts = 0;
    new->incremented_opts = 0;
    new->decremented_opts = 0;
    new->default_keyid = '\0';
    new->default_direction = '\0';

    return (void *) new;
}