const char *
Ssl::ErrorDetailsManager::getDefaultErrorDetail(Security::ErrorCode value)
{
    return theDefaultErrorDetails->getErrorDetail(value);
}