const char *
Ssl::ErrorDetailsList::getErrorDetail(Security::ErrorCode value)
{
    const ErrorDetails::const_iterator it = theList.find(value);
    if (it != theList.end()) {
        return it->second.detail.termedBuf();
    }

    return NULL;
}