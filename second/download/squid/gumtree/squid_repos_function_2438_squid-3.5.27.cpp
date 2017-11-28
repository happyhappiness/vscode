void
HeaderManglers::dumpAccess(StoreEntry * entry, const char *name) const
{
    for (int i = 0; i < HDR_ENUM_END; ++i) {
        header_mangler_dump_access(entry, name, known[i],
                                   httpHeaderNameById(i));
    }

    typedef ManglersByName::const_iterator MBNCI;
    for (MBNCI i = custom.begin(); i != custom.end(); ++i)
        header_mangler_dump_access(entry, name, i->second, i->first.c_str());

    header_mangler_dump_access(entry, name, all, "All");
}