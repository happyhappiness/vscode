
/** Default behaviour is to expose nothing */
void
Auth::Config::registerWithCacheManager(void)
{}

Auth::User::Pointer
Auth::Config::findUserInCache(const char *nameKey, Auth::Type authType)
{
    AuthUserHashPointer *usernamehash;
    debugs(29, 9, "Looking for user '" << nameKey << "'");

