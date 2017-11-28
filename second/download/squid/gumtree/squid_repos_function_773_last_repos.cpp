static void
parse_cachedir(Store::DiskConfig *swap)
{
    char *type_str = ConfigParser::NextToken();
    if (!type_str) {
        self_destruct();
        return;
    }

    char *path_str = ConfigParser::NextToken();
    if (!path_str) {
        self_destruct();
        return;
    }

    int fs = find_fstype(type_str);
    if (fs < 0) {
        debugs(3, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: This proxy does not support the '" << type_str << "' cache type. Ignoring.");
        return;
    }

    /* reconfigure existing dir */

    RefCount<SwapDir> sd;
    for (int i = 0; i < swap->n_configured; ++i) {
        assert (swap->swapDirs[i].getRaw());

        if ((strcasecmp(path_str, dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw())->path)) == 0) {
            /* this is specific to on-fs Stores. The right
             * way to handle this is probably to have a mapping
             * from paths to stores, and have on-fs stores
             * register with that, and lookip in that in their
             * own setup logic. RBC 20041225. TODO.
             */

            sd = dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw());

            if (strcmp(sd->type(), StoreFileSystem::FileSystems().at(fs)->type()) != 0) {
                debugs(3, DBG_CRITICAL, "ERROR: Can't change type of existing cache_dir " <<
                       sd->type() << " " << sd->path << " to " << type_str << ". Restart required");
                return;
            }

            sd->reconfigure();
            return;
        }
    }

    /* new cache_dir */
    if (swap->n_configured > 63) {
        /* 7 bits, signed */
        debugs(3, DBG_CRITICAL, "WARNING: There is a fixed maximum of 63 cache_dir entries Squid can handle.");
        debugs(3, DBG_CRITICAL, "WARNING: '" << path_str << "' is one to many.");
        self_destruct();
        return;
    }

    allocate_new_swapdir(swap);

    swap->swapDirs[swap->n_configured] = StoreFileSystem::FileSystems().at(fs)->createSwapDir();

    sd = dynamic_cast<SwapDir *>(swap->swapDirs[swap->n_configured].getRaw());

    /* parse the FS parameters and options */
    sd->parse(swap->n_configured, path_str);

    ++swap->n_configured;
}