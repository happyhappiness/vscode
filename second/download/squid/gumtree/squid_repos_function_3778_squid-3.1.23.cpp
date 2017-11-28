void
Adaptation::Config::DumpAccess(StoreEntry *entry, const char *name)
{
    LOCAL_ARRAY(char, nom, 64);

    typedef AccessRules::iterator CI;
    for (CI i = AllRules().begin(); i != AllRules().end(); ++i) {
        snprintf(nom, 64, "%s " SQUIDSTRINGPH, name, SQUIDSTRINGPRINT((*i)->groupId));
        dump_acl_access(entry, nom, (*i)->acl);
    }
}