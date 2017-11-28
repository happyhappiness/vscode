headerMangler *
HeaderManglers::track(const char *name)
{
    if (strcmp(name, "All") == 0)
        return &all;

    const Http::HdrType id = Http::HeaderLookupTable.lookup(SBuf(name)).id;

    if (id != Http::HdrType::BAD_HDR)
        return &known[id];

    if (strcmp(name, "Other") == 0)
        return &known[Http::HdrType::OTHER];

    return &custom[name];
}