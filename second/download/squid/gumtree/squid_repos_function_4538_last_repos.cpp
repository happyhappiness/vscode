void
Store::Disks::markForUnlink(StoreEntry &e) {
    if (e.swap_filen >= 0)
        store(e.swap_dirn)->markForUnlink(e);
}