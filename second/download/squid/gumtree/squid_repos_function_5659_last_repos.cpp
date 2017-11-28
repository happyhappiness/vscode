void
Auth::User::CredentialsCacheStats(StoreEntry *output)
{
    auto userlist = authenticateCachedUsersList();
    storeAppendPrintf(output, "Cached Usernames: %d", static_cast<int32_t>(userlist.size()));
    storeAppendPrintf(output, "\n%-15s %-9s %-9s %-9s %s\t%s\n",
                      "Type",
                      "State",
                      "Check TTL",
                      "Cache TTL",
                      "Username", "Key");
    storeAppendPrintf(output, "--------------- --------- --------- --------- ------------------------------\n");
    for ( auto auth_user : userlist ) {
        storeAppendPrintf(output, "%-15s %-9s %-9d %-9d %s\t" SQUIDSBUFPH "\n",
                          Auth::Type_str[auth_user->auth_type],
                          CredentialState_str[auth_user->credentials()],
                          auth_user->ttl(),
                          static_cast<int32_t>(auth_user->expiretime - squid_curtime + ::Config.authenticateTTL),
                          auth_user->username(),
                          SQUIDSBUFPRINT(auth_user->userKey())
                         );
    }
}