static int cmp_provider_groups(const void *a_, const void *b_)
{
    const ap_list_provider_groups_t *a = a_, *b = b_;
    int ret = strcmp(a->provider_group, b->provider_group);
    if (!ret)
        ret = strcmp(a->provider_version, b->provider_version);
    return ret;
}