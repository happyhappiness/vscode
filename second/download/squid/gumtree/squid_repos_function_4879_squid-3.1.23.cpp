const char *
AuthBasicConfig::type() const
{
    return basicScheme::GetInstance().type();
}