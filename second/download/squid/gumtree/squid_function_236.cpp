static
void header_mangler_dump_replacement(StoreEntry * entry, const char *option,
                                     const header_mangler &m, const char *name)
{
    if (m.replacement)
        storeAppendPrintf(entry, "%s %s %s\n", option, name, m.replacement);
}