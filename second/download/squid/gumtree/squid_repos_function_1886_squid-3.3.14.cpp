static void
checkDepend(const std::string &directive, const char *name, const TypeList &types, const EntryList &entries)
{
    for (TypeList::const_iterator t = types.begin(); t != types.end(); ++t) {
        if (t->name.compare(name) != 0)
            continue;
        for (TypeDepList::const_iterator dep = t->depend.begin(); dep != t->depend.end(); ++dep) {
            EntryList::const_iterator entry = entries.begin();
            for (; entry != entries.end(); ++entry) {
                if (entry->name.compare(*dep) == 0)
                    break;
            }
            if (entry == entries.end()) {
                std::cerr << "ERROR: '" << directive << "' (" << name << ") depends on '" << *dep << "'\n";
                exit(1);
            }
        }
        return;
    }
    std::cerr << "ERROR: Dependencies for cf.data type '" << name << "' used in ' " << directive << "' not defined\n" ;
    exit(1);
}