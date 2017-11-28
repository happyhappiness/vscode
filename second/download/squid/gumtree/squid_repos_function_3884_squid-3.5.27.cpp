Adaptation::AccessRule *
Adaptation::FindRuleByGroupId(const String &groupId)
{
    typedef AccessRules::iterator ARI;
    for (ARI i = AllRules().begin(); i != AllRules().end(); ++i) {
        if ((*i)->groupId == groupId)
            return *i;
    }

    return NULL;
}