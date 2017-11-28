AuthScheme &
ntlmScheme::GetInstance()
{
    if (_instance == NULL)
        _instance = new ntlmScheme();
    return *_instance;
}