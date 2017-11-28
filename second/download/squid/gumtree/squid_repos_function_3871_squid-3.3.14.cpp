void
Adaptation::Config::removeRule(const String& id)
{
    typedef AccessRules::const_iterator ARI;
    const AccessRules& rules = AllRules();
    for (ARI it = rules.begin(); it != rules.end(); ++it) {
        AccessRule* rule = *it;
        if (rule->groupId == id) {
            debugs(93, 5, HERE << "removing access rules for:" << id);
            AllRules().prune(rule);
            delete (rule);
            break;
        }
    }
}