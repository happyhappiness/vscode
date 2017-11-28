const char *
Ssl::ErrorDetailsList::getErrorDescr(Security::ErrorCode value)
{
    const ErrorDetails::const_iterator it = theList.find(value);
    if (it != theList.end()) {
        return it->second.descr.termedBuf();
    }

    return NULL;
}