PconnModule *
PconnModule::GetInstance()
{
    if (instance == NULL)
        instance = new PconnModule;

    return instance;
}