int32_t
Auth::Ntlm::User::ttl() const
{
    return -1; // NTLM credentials cannot be cached.
}