headerMangler *
HeaderManglers::track(const char *name)
{
    int id = httpHeaderIdByNameDef(name, strlen(name));

    if (id == HDR_BAD_HDR) { // special keyword or a custom header
        if (strcmp(name, "All") == 0)
            id = HDR_ENUM_END;
        else if (strcmp(name, "Other") == 0)
            id = HDR_OTHER;
    }

    headerMangler *m = NULL;
    if (id == HDR_ENUM_END) {
        m = &all;
    } else if (id == HDR_BAD_HDR) {
        m = &custom[name];
    } else {
        m = &known[id]; // including HDR_OTHER
    }

    assert(m);
    return m;
}