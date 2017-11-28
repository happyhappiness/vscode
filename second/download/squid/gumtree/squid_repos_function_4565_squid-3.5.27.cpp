const char *
Ssl::ErrorDetailsManager::getDefaultErrorDetail(Ssl::ssl_error_t value)
{
    return theDefaultErrorDetails->getErrorDetail(value);
}