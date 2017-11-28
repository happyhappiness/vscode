bool
Auth::Ntlm::Config::active() const
{
    return authntlm_initialised == 1;
}