SBufList
ACLSslErrorData::dump() const
{
    SBufList sl;
    Ssl::Errors *data = values;
    while (data != NULL) {
        sl.push_back(SBuf(Ssl::GetErrorName(data->element)));
        data = data->next;
    }
    return sl;
}