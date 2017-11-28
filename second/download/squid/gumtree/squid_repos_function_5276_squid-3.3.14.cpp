Auth::Config *
Auth::Ntlm::Scheme::createConfig()
{
    Auth::Ntlm::Config *ntlmCfg = new Auth::Ntlm::Config;
    return dynamic_cast<Auth::Config*>(ntlmCfg);
}