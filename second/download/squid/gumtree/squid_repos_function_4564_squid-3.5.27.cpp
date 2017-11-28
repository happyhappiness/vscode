const char *
Ssl::ErrorDetailsManager::getDefaultErrorDescr(Ssl::ssl_error_t value)
{
    return theDefaultErrorDetails->getErrorDescr(value);
}