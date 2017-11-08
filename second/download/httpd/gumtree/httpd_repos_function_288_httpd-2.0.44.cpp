const dav_provider * dav_lookup_provider(const char *name)
{
    return ap_lookup_provider(DAV_PROVIDER_GROUP, name, "0");
}