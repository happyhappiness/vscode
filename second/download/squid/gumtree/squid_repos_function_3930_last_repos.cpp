const String &Ssl::ErrorDetail::toString() const
{
    if (errDetailStr.size() == 0)
        buildDetail();
    return errDetailStr;
}