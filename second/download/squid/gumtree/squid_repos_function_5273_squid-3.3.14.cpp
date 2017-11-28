Auth::Scheme::Pointer
Auth::Ntlm::Scheme::GetInstance()
{
    if (_instance == NULL) {
        _instance = new Auth::Ntlm::Scheme();
        AddScheme(_instance);
    }
    return _instance;
}