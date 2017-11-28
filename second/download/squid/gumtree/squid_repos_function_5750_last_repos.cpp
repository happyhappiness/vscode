Auth::Scheme::Pointer
Auth::Negotiate::Scheme::GetInstance()
{
    if (_instance == NULL) {
        _instance = new Auth::Negotiate::Scheme();
        AddScheme(_instance);
    }
    return _instance;
}