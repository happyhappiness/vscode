static void *create_setenvif_config(apr_pool_t *p)
{
    sei_cfg_rec *new = (sei_cfg_rec *) apr_palloc(p, sizeof(sei_cfg_rec));

    new->conditionals = apr_array_make(p, 20, sizeof(sei_entry));
    return (void *) new;
}