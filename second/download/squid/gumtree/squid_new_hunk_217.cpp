            l->delAt(p, headers_deleted);

    if (headers_deleted)
        l->refreshMask();
}

static
void header_mangler_clean(header_mangler &m)
{
    aclDestroyAccessList(&m.access_list);
    safe_free(m.replacement);
}

static
void header_mangler_dump_access(StoreEntry * entry, const char *option,
                                const header_mangler &m, const char *name)
{
    if (m.access_list != NULL) {
        storeAppendPrintf(entry, "%s ", option);
        dump_acl_access(entry, name, m.access_list);
    }
}

static
void header_mangler_dump_replacement(StoreEntry * entry, const char *option,
                                     const header_mangler &m, const char *name)
{
    if (m.replacement)
        storeAppendPrintf(entry, "%s %s %s\n", option, name, m.replacement);
}

HeaderManglers::HeaderManglers()
{
    memset(known, 0, sizeof(known));
    memset(&all, 0, sizeof(all));
}

HeaderManglers::~HeaderManglers()
{
    for (int i = 0; i < HDR_ENUM_END; ++i)
        header_mangler_clean(known[i]);

    typedef ManglersByName::iterator MBNI;
    for (MBNI i = custom.begin(); i != custom.end(); ++i)
        header_mangler_clean(i->second);

    header_mangler_clean(all);
}

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

void
HeaderManglers::dumpReplacement(StoreEntry * entry, const char *name) const
{
    for (int i = 0; i < HDR_ENUM_END; ++i) {
        header_mangler_dump_replacement(entry, name, known[i],
                                        httpHeaderNameById(i));
    }

    typedef ManglersByName::const_iterator MBNCI;
    for (MBNCI i = custom.begin(); i != custom.end(); ++i) {
        header_mangler_dump_replacement(entry, name, i->second,
                                        i->first.c_str());
    }

    header_mangler_dump_replacement(entry, name, all, "All");
}

header_mangler *
HeaderManglers::track(const char *name)
{
    int id = httpHeaderIdByNameDef(name, strlen(name));

    if (id == HDR_BAD_HDR) { // special keyword or a custom header
        if (strcmp(name, "All") == 0)
            id = HDR_ENUM_END;
        else if (strcmp(name, "Other") == 0)
            id = HDR_OTHER;
    }

    header_mangler *m = NULL;
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

void
HeaderManglers::setReplacement(const char *name, const char *value)
{
    // for backword compatibility, we allow replacements to be configured
    // for headers w/o access rules, but such replacements are ignored
    header_mangler *m = track(name);

    safe_free(m->replacement); // overwrite old value if any
    m->replacement = xstrdup(value);
}

const header_mangler *
HeaderManglers::find(const HttpHeaderEntry &e) const
{
    // a known header with a configured ACL list
    if (e.id != HDR_OTHER && 0 <= e.id && e.id < HDR_ENUM_END &&
            known[e.id].access_list)
        return &known[e.id];

    // a custom header
    if (e.id == HDR_OTHER) {
        // does it have an ACL list configured?
        // Optimize: use a name type that we do not need to convert to here
        const ManglersByName::const_iterator i = custom.find(e.name.termedBuf());
        if (i != custom.end())
            return &i->second;
    }

    // Next-to-last resort: "Other" rules match any custom header
    if (e.id == HDR_OTHER && known[HDR_OTHER].access_list)
        return &known[HDR_OTHER];

    // Last resort: "All" rules match any header
    if (all.access_list)
        return &all;

    return NULL;
}

