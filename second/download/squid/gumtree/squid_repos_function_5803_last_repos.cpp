void
Auth::Basic::User::addToNameCache()
{
    Cache()->insert(userKey(), this);
}