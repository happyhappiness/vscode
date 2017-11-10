static void *merge_action_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    action_dir_config *base = (action_dir_config *) basev;
    action_dir_config *add = (action_dir_config *) addv;
    action_dir_config *new = (action_dir_config *) apr_palloc(p,
                                  sizeof(action_dir_config));
    int i;

    new->action_types = apr_table_overlay(p, add->action_types,
                                       base->action_types);

    for (i = 0; i < METHODS; ++i) {
        new->scripted[i] = add->scripted[i] ? add->scripted[i]
                                            : base->scripted[i];
    }

    new->configured = (base->configured || add->configured);
    return new;
}