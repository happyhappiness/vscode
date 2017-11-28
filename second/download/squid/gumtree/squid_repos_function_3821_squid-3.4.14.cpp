Adaptation::Services &
Adaptation::AllServices()
{
    static Services *TheServices = new Services;
    return *TheServices;
}