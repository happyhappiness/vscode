const dav_hooks_search *dav_get_search_hooks(request_rec *r)
{
    return dav_get_provider(r)->search;
}