static void *merge_expires_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    expires_dir_config *new = (expires_dir_config *) apr_pcalloc(p, sizeof(expires_dir_config));
    expires_dir_config *base = (expires_dir_config *) basev;
    expires_dir_config *add = (expires_dir_config *) addv;

    if (add->active == ACTIVE_DONTCARE) {
        new->active = base->active;
    }
    else {
        new->active = add->active;
    }

    if (add->expiresdefault[0] != '\0') {
        new->expiresdefault = add->expiresdefault;
    }
    else {
	new->expiresdefault = base->expiresdefault;
    }

    new->expiresbytype = apr_table_overlay(p, add->expiresbytype,
                                        base->expiresbytype);
    return new;
}