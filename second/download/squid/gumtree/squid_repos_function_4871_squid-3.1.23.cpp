AuthScheme &
negotiateScheme::GetInstance()
{
    if (_instance == NULL)
        _instance = new negotiateScheme();
    return *_instance;
}