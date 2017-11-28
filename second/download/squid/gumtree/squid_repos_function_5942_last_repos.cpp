void
Auth::Digest::User::addToNameCache()
{
    Cache()->insert(userKey(), this);
}