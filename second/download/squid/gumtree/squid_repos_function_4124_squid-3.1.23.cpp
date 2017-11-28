const String &Ssl::ErrorDetail::toString() const
{
    if (!errDetailStr.defined())
        buildDetail();
    return errDetailStr;
}