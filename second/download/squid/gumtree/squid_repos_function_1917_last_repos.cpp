void
HeaderManglers::dumpAccess(StoreEntry * entry, const char *name) const
{
    for (auto id : WholeEnum<Http::HdrType>())
        header_mangler_dump_access(entry, name, known[id], Http::HeaderLookupTable.lookup(id).name);

    for (auto i : custom)
        header_mangler_dump_access(entry, name, i.second, i.first.c_str());

    header_mangler_dump_access(entry, name, all, "All");
}