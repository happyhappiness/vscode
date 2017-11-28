Auth::Scheme::Pointer
Auth::Digest::Scheme::GetInstance()
{
    if (_instance == NULL) {
        _instance = new Auth::Digest::Scheme();
        AddScheme(_instance);
    }
    return _instance;
}