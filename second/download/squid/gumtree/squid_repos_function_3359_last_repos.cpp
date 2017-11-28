void
Adaptation::Config::parseService()
{
    ServiceConfigPointer cfg = newServiceConfig();
    if (!cfg->parse()) {
        fatalf("%s:%d: malformed adaptation service configuration",
               cfg_filename, config_lineno);
    }
    serviceConfigs.push_back(cfg);
}