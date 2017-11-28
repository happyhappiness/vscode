Adaptation::AccessRule *
Adaptation::FindRule(const AccessRule::Id &id)
{
    typedef AccessRules::iterator ARI;
    for (ARI i = AllRules().begin(); i != AllRules().end(); ++i) {
        if ((*i)->id == id)
            return *i;
    }

    return NULL;
}