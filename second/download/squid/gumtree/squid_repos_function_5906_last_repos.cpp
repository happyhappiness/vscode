const char *
Auth::Ntlm::Config::type() const
{
    return Auth::Ntlm::Scheme::GetInstance()->type();
}