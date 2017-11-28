const char *
Ssl::ErrorDetailsManager::getDefaultErrorDescr(Security::ErrorCode value)
{
    return theDefaultErrorDetails->getErrorDescr(value);
}