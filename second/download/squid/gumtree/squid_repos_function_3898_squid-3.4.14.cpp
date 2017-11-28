void
Adaptation::Config::freeService()
{
    FreeAccess();
    FreeServiceGroups();

    DetachServices();

    serviceConfigs.clean();
}