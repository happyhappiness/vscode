Adaptation::ServiceConfigPointer
Adaptation::Config::findServiceConfig(const String &service)
{
    typedef ServiceConfigs::const_iterator SCI;
    const ServiceConfigs& configs = serviceConfigs;
    for (SCI cfg = configs.begin(); cfg != configs.end(); ++cfg) {
        if ((*cfg)->key == service)
            return *cfg;
    }
    return NULL;
}