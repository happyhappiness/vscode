int32_t
Auth::Basic::User::ttl() const
{
    if (credentials() != Auth::Ok && credentials() != Auth::Pending)
        return -1; // TTL is obsolete NOW.

    int32_t basic_ttl = expiretime - squid_curtime + static_cast<Auth::Basic::Config*>(config)->credentialsTTL;
    int32_t global_ttl = static_cast<int32_t>(expiretime - squid_curtime + ::Config.authenticateTTL);

    return min(basic_ttl, global_ttl);
}