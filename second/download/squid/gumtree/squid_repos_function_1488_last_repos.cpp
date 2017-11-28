bool
external_acl::maybeCacheable(const allow_t &result) const
{
    if (cache_size <= 0)
        return false; // cache is disabled

    if (result == ACCESS_DUNNO)
        return false; // non-cacheable response

    if ((result.allowed() ? ttl : negative_ttl) <= 0)
        return false; // not caching this type of response

    return true;
}