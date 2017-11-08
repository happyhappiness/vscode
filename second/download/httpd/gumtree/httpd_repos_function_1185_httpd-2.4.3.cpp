static cache_provider_list *get_provider(request_rec *r, struct cache_enable *ent,
        cache_provider_list *providers)
{
    /* Fetch from global config and add to the list. */
    cache_provider *provider;
    provider = ap_lookup_provider(CACHE_PROVIDER_GROUP, ent->type,
                                  "0");
    if (!provider) {
        /* Log an error! */
    }
    else {
        cache_provider_list *newp;
        newp = apr_pcalloc(r->pool, sizeof(cache_provider_list));
        newp->provider_name = ent->type;
        newp->provider = provider;

        if (!providers) {
            providers = newp;
        }
        else {
            cache_provider_list *last = providers;

            while (last->next) {
                if (last->provider == provider) {
                    return providers;
                }
                last = last->next;
            }
            if (last->provider == provider) {
                return providers;
            }
            last->next = newp;
        }
    }

    return providers;
}