void
AuthUser::addToNameCache()
{
    usernamehash = new AuthUserHashPointer (this);
}