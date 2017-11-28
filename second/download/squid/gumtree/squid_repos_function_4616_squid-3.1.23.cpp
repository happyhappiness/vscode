void
CossSwapDir::create()
{
    debugs (47, 3, "Creating swap space in " << path);

    struct stat swap_sb;
    int swap;

    if (::stat(path, &swap_sb) < 0) {
        debugs (47, 2, "COSS swap space space being allocated.");
#ifdef _SQUID_MSWIN_

        mkdir(path);
#else

        mkdir(path, 0700);
#endif

    }

    /* should check here for directories instead of files, and for file size
     * TODO - if nothing changes, there is nothing to do
     */
    swap = open(stripePath(), O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0600);

    /* TODO just set the file size */
    /* swap size is in K */
    char *block[1024];

    memset(&block, '\0', 1024);

    for (off_t offset = 0; offset < max_size; ++offset) {
        if (write (swap, block, 1024) < 1024) {
            debugs (47, 0, "Failed to create COSS swap space in " << path);
        }
    }

    close (swap);

}