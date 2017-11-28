void
HeaderManglers::setReplacement(const char *name, const char *value)
{
    // for backword compatibility, we allow replacements to be configured
    // for headers w/o access rules, but such replacements are ignored
    headerMangler *m = track(name);

    safe_free(m->replacement); // overwrite old value if any
    m->replacement = xstrdup(value);
}