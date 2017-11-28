{
    for (Auth::ConfigVector::iterator  i = cfg.begin(); i != cfg.end(); ++i)
        (*i)->dump(entry, name, (*i));
}
#endif /* USE_AUTH */

/* TODO: just return the object, the # is irrelevant */
static int
find_fstype(char *type)
{
    for (size_t i = 0; i < StoreFileSystem::FileSystems().size(); ++i)
        if (strcasecmp(type, StoreFileSystem::FileSystems().at(i)->type()) == 0)
            return (int)i;

    return (-1);
}

static void
parse_cachedir(SquidConfig::_cacheSwap * swap)
{
    char *type_str;
    char *path_str;
    RefCount<SwapDir> sd;
    int i;
    int fs;

    if ((type_str = ConfigParser::NextToken()) == NULL)
        self_destruct();

    if ((path_str = ConfigParser::NextToken()) == NULL)
        self_destruct();

    fs = find_fstype(type_str);

    if (fs < 0) {
        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: This proxy does not support the '" << type_str << "' cache type. Ignoring.");
        return;
    }

    /* reconfigure existing dir */

    for (i = 0; i < swap->n_configured; ++i) {
        assert (swap->swapDirs[i].getRaw());

        if ((strcasecmp(path_str, dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw())->path)) == 0) {
            /* this is specific to on-fs Stores. The right
             * way to handle this is probably to have a mapping
             * from paths to stores, and have on-fs stores
