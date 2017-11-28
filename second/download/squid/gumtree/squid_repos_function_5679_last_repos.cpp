Auth::User::Pointer
CredentialsCache::lookup(const SBuf &userKey) const
{
    debugs(29, 6, "lookup for " << userKey);
    auto p = store_.find(userKey);
    if (p == store_.end())
        return User::Pointer(nullptr);
    return p->second;
}