AuthScheme &
basicScheme::GetInstance()
{
    if (_instance == NULL)
        _instance = new basicScheme();
    return *_instance;
}