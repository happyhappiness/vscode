static void *create_neg_dir_config(apr_pool_t *p, char *dummy)
{
    neg_dir_config *new = (neg_dir_config *) apr_palloc(p, sizeof(neg_dir_config));

    new->forcelangpriority = FLP_UNDEF;
    new->language_priority = NULL;
    return new;
}