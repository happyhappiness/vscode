void
Adaptation::Config::clear()
{
    debugs(93, 3, HERE << "rules: " << AllRules().size() << ", groups: " <<
           AllGroups().size() << ", services: " << serviceConfigs.size());
    typedef ServiceConfigs::const_iterator SCI;
    const ServiceConfigs& configs = serviceConfigs;
    for (SCI cfg = configs.begin(); cfg != configs.end(); ++cfg)
        removeService((*cfg)->key);
    serviceConfigs.clean();
    debugs(93, 3, HERE << "rules: " << AllRules().size() << ", groups: " <<
           AllGroups().size() << ", services: " << serviceConfigs.size());
}