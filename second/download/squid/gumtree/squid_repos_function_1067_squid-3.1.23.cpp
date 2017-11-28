static void
parse_cachedir(SquidConfig::_cacheSwap * swap)
{
    char *type_str;
    char *path_str;
    RefCount<SwapDir> sd;
    int i;
    int fs;

    if ((type_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    if ((path_str = strtok(NULL, w_space)) == NULL)
        self_destruct();

    fs = find_fstype(type_str);

    if (fs < 0)
        self_destruct();

    /* reconfigure existing dir */

    for (i = 0; i < swap->n_configured; i++) {
        assert (swap->swapDirs[i].getRaw());

        if ((strcasecmp(path_str, dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw())->path)) == 0) {
            /* this is specific to on-fs Stores. The right
             * way to handle this is probably to have a mapping
             * from paths to stores, and have on-fs stores
             * register with that, and lookip in that in their
             * own setup logic. RBC 20041225. TODO.
             */

            sd = dynamic_cast<SwapDir *>(swap->swapDirs[i].getRaw());

            if (sd->type() != StoreFileSystem::FileSystems().items[fs]->type()) {
                debugs(3, 0, "ERROR: Can't change type of existing cache_dir " <<
                       sd->type() << " " << sd->path << " to " << type_str << ". Restart required");
                return;
            }

            sd->reconfigure (i, path_str);

            update_maxobjsize();

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

    swap->swapDirs[swap->n_configured] = StoreFileSystem::FileSystems().items[fs]->createSwapDir();

    sd = dynamic_cast<SwapDir *>(swap->swapDirs[swap->n_configured].getRaw());

    /* parse the FS parameters and options */
    sd->parse(swap->n_configured, path_str);

    ++swap->n_configured;

    /* Update the max object size */
    update_maxobjsize();
}