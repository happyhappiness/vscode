const char *
AuthNTLMConfig::type() const
{
    return ntlmScheme::GetInstance().type();
}