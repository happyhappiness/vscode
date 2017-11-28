void
Auth::Negotiate::User::addToNameCache()
{
    Cache()->insert(userKey(), this);
}