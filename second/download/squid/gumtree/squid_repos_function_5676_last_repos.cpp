std::vector<Auth::User::Pointer>
authenticateCachedUsersList()
{
    auto aucp_compare = [=](const Auth::User::Pointer lhs, const Auth::User::Pointer rhs) {
        return lhs->userKey() < rhs->userKey();
    };
    std::vector<Auth::User::Pointer> v1, v2, rv, u1, u2;
#if HAVE_AUTH_MODULE_BASIC
    if (Auth::Config::Find("basic") != nullptr)
        u1 = Auth::Basic::User::Cache()->sortedUsersList();
#endif
#if HAVE_AUTH_MODULE_DIGEST
    if (Auth::Config::Find("digest") != nullptr)
        u2 = Auth::Digest::User::Cache()->sortedUsersList();
#endif
    if (u1.size() > 0 || u2.size() > 0) {
        v1.reserve(u1.size()+u2.size());
        std::merge(u1.begin(), u1.end(),u2.begin(), u2.end(),
                   std::back_inserter(v1), aucp_compare);
        u1.clear();
        u2.clear();
    }
#if HAVE_AUTH_MODULE_NEGOTIATE
    if (Auth::Config::Find("negotiate") != nullptr)
        u1 = Auth::Negotiate::User::Cache()->sortedUsersList();
#endif
#if HAVE_AUTH_MODULE_NTLM
    if (Auth::Config::Find("ntlm") != nullptr)
        u2 = Auth::Ntlm::User::Cache()->sortedUsersList();
#endif
    if (u1.size() > 0 || u2.size() > 0) {
        v2.reserve(u1.size()+u2.size());
        std::merge(u1.begin(), u1.end(),u2.begin(), u2.end(),
                   std::back_inserter(v2), aucp_compare);
    }
    rv.reserve(v1.size()+v2.size());
    std::merge(v1.begin(), v1.end(),v2.begin(), v2.end(),
               std::back_inserter(rv), aucp_compare);
    return rv;
}