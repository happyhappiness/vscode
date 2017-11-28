void
Auth::User::addToNameCache()
{
    /* AuthUserHashPointer will self-register with the username cache */
    new AuthUserHashPointer(this);
}