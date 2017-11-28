void
Store::Disks::unlink(StoreEntry &e) {
    if (e.swap_filen >= 0)
        store(e.swap_dirn)->unlink(e);
}