int
Fs::Ufs::UFSSwapDir::createDirectory(const char *aPath, int should_exist)
{
    int created = 0;

    struct stat st;
    getCurrentTime();

    if (0 == ::stat(aPath, &st)) {
        if (S_ISDIR(st.st_mode)) {
            debugs(47, (should_exist ? 3 : DBG_IMPORTANT), aPath << " exists");
        } else {
            fatalf("Swap directory %s is not a directory.", aPath);
        }
    } else if (0 == mkdir(aPath, 0755)) {
        debugs(47, (should_exist ? DBG_IMPORTANT : 3), aPath << " created");
        created = 1;
    } else {
        fatalf("Failed to make swap directory %s: %s",
               aPath, xstrerror());
    }

    return created;
}