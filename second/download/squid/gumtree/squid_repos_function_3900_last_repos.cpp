bool
Ssl::ErrorDetailsList::getRecord(Security::ErrorCode value, ErrorDetailEntry &entry)
{
    const ErrorDetails::const_iterator it = theList.find(value);
    if (it != theList.end()) {
        entry.error_no =  it->second.error_no;
        entry.name =  it->second.name;
        entry.detail =  it->second.detail;
        entry.descr =  it->second.descr;
        return true;
    }
    return false;
}