void
CossSwapDir::create()
{
    debugs (47, 3, "Creating swap space in " << path);

    struct stat swap_sb;
    int swap;

    if (::stat(path, &swap_sb) < 0) {
        debugs (47, 2, "COSS swap space space being allocated.");
        mkdir(path, 0700);
    }

    /* should check here for directories instead of files, and for file size
     * TODO - if nothing changes, there is nothing to do
     */
    swap = open(stripePath(), O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0600);

    /* TODO just set the file size */
    char block[1024];
    Must(maxSize() % sizeof(block) == 0);
    memset(block, '\0', sizeof(block));

    for (uint64_t offset = 0; offset < maxSize(); offset += sizeof(block)) {
        if (write (swap, block, sizeof(block)) != sizeof(block)) {
            debugs (47, 0, "Failed to create COSS swap space in " << path);
        }
    }

    close (swap);

}