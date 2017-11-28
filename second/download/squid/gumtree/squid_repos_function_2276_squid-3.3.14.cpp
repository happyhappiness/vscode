static
void header_mangler_clean(headerMangler &m)
{
    aclDestroyAccessList(&m.access_list);
    safe_free(m.replacement);
}