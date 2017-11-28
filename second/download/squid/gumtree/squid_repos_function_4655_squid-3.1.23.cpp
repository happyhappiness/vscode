int
UFSSwapDir::createDirectory(const char *aPath, int should_exist)
{
    int created = 0;

    struct stat st;
    getCurrentTime();

    if (0 == ::stat(aPath, &st)) {
        if (S_ISDIR(st.st_mode)) {
            debugs(47, (should_exist ? 3 : 1), aPath << " exists");
        } else {
            fatalf("Swap directory %s is not a directory.", aPath);
        }

#ifdef _SQUID_MSWIN_

    } else if (0 == mkdir(aPath)) {
#else

    } else if (0 == mkdir(aPath, 0755)) {
#endif
        debugs(47, (should_exist ? 1 : 3), aPath << " created");
        created = 1;
    } else {
        fatalf("Failed to make swap directory %s: %s",
               aPath, xstrerror());
    }

    return created;
}