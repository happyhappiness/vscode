const char *
AuthDigestConfig::type() const
{
    return digestScheme::GetInstance().type();
}