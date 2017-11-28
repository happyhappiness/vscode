bool
AuthNTLMConfig::active() const
{
    return authntlm_initialised == 1;
}