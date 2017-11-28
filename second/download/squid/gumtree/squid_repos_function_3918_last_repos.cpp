const char *
Ssl::GetErrorDescr(Security::ErrorCode value)
{
    return ErrorDetailsManager::GetInstance().getDefaultErrorDescr(value);
}