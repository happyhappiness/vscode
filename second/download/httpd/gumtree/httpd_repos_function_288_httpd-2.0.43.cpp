const dav_provider * dav_lookup_provider(const char *name)
{
    /* Better watch out against no registered providers */
    if (dav_repos_providers == NULL) {
        return NULL;
    }

    return apr_hash_get(dav_repos_providers, name, APR_HASH_KEY_STRING);
}