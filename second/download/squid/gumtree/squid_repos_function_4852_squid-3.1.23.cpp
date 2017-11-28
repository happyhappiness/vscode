const char *
AuthNegotiateConfig::type() const
{
    return negotiateScheme::GetInstance().type();
}