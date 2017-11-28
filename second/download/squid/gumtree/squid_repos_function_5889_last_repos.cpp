void
Auth::Ntlm::User::addToNameCache()
{
    Cache()->insert(userKey(), this);
}