static int cmp_provider_names(const void *a_, const void *b_)
{
    const ap_list_provider_names_t *a = a_, *b = b_;
    return strcmp(a->provider_name, b->provider_name);
}