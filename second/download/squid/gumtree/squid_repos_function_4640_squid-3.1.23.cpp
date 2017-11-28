void
UFSSwapDir::init()
{
    debugs(47, 3, "Initialising UFS SwapDir engine.");
    /* Parsing must be finished by now - force to NULL, don't delete */
    currentIOOptions = NULL;
    static int started_clean_event = 0;
    static const char *errmsg =
        "\tFailed to verify one of the swap directories, Check cache.log\n"
        "\tfor details.  Run 'squid -z' to create swap directories\n"
        "\tif needed, or if running Squid for the first time.";
    IO->init();

    if (verifyCacheDirs())
        fatal(errmsg);

    openLog();

    rebuild();

    if (!started_clean_event) {
        eventAdd("UFS storeDirClean", CleanEvent, NULL, 15.0, 1);
        started_clean_event = 1;
    }

    (void) storeDirGetBlkSize(path, &fs.blksize);
}