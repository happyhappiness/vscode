int32_t
Auth::Negotiate::User::ttl() const
{
    return -1; // Negotiate cannot be cached.
}