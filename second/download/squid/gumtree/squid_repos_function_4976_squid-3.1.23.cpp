AuthScheme &
digestScheme::GetInstance()
{
    if (_instance == NULL)
        _instance = new digestScheme();
    return *_instance;
}