void
Fs::Ufs::UFSSwapDir::createSwapSubDirs()
{
    LOCAL_ARRAY(char, name, MAXPATHLEN);

    for (int i = 0; i < l1; ++i) {
        snprintf(name, MAXPATHLEN, "%s/%02X", path, i);

        int should_exist;

        if (createDirectory(name, 0))
            should_exist = 0;
        else
            should_exist = 1;

        debugs(47, DBG_IMPORTANT, "Making directories in " << name);

        for (int k = 0; k < l2; ++k) {
            snprintf(name, MAXPATHLEN, "%s/%02X/%02X", path, i, k);
            createDirectory(name, should_exist);
        }
    }
}