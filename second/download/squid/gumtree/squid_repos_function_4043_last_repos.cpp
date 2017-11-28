SBufList
ACLSslErrorData::dump() const
{
    SBufList sl;
    for (const auto &e : values) {
        sl.push_back(SBuf(Ssl::GetErrorName(e)));
    }
    return sl;
}