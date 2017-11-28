std::vector<Auth::User::Pointer>
CredentialsCache::sortedUsersList() const
{
    std::vector<Auth::User::Pointer> rv(size(), nullptr);
    std::transform(store_.begin(), store_.end(), rv.begin(),
    [](StoreType::value_type v) { return v.second; }
                  );
    std::sort(rv.begin(), rv.end(),
    [](const Auth::User::Pointer &lhs, const Auth::User::Pointer &rhs) {
        return strcmp(lhs->username(), rhs->username()) < 0;
    }
             );
    return rv;
}