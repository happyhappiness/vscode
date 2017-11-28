void
CredentialsCache::insert(const SBuf &userKey, Auth::User::Pointer anAuth_user)
{
    debugs(29, 6, "adding " << userKey << " (" << anAuth_user->username() << ")");
    store_[userKey] = anAuth_user;
    scheduleCleanup();
}