static void *merge_neg_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    neg_dir_config *base = (neg_dir_config *) basev;
    neg_dir_config *add = (neg_dir_config *) addv;
    neg_dir_config *new = (neg_dir_config *) apr_palloc(p, sizeof(neg_dir_config));

    /* give priority to the config in the subdirectory */
    new->forcelangpriority = (add->forcelangpriority != FLP_UNDEF)
				? add->forcelangpriority 
				: base->forcelangpriority;
    new->language_priority = add->language_priority 
				? add->language_priority 
                                : base->language_priority;
    return new;
}