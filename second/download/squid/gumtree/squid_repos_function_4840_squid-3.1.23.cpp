Vector<AuthScheme*> &
AuthScheme::GetSchemes()
{
    if (!_Schemes)
        _Schemes = new Vector<AuthScheme *>;

    return *_Schemes;
}