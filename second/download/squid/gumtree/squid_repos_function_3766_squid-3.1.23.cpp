void
Adaptation::Config::freeService()
{
    FreeAccess();
    FreeServiceGroups();

    DetachServices();

    while (!serviceConfigs.empty()) {
        delete serviceConfigs.back();
        serviceConfigs.pop_back();
    }
}