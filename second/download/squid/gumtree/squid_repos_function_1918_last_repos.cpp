void
HeaderManglers::dumpReplacement(StoreEntry * entry, const char *name) const
{
    for (auto id : WholeEnum<Http::HdrType>()) {
        header_mangler_dump_replacement(entry, name, known[id], Http::HeaderLookupTable.lookup(id).name);
    }

    for (auto i: custom) {
        header_mangler_dump_replacement(entry, name, i.second, i.first.c_str());
    }

    header_mangler_dump_replacement(entry, name, all, "All");
}