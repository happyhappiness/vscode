bool
ACLSslErrorData::match(Ssl::ssl_error_t toFind)
{
    return values->findAndTune (toFind);
}