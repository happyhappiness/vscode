Auth::Scheme::Pointer
Auth::Basic::Scheme::GetInstance()
{
    if (_instance == NULL) {
        _instance = new Auth::Basic::Scheme();
        AddScheme(_instance);
    }
    return _instance;
}