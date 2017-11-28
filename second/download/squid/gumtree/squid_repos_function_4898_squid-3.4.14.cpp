void
Rock::SwapDir::create()
{
    assert(path);
    assert(filePath);

    if (UsingSmp() && !IamDiskProcess()) {
        debugs (47,3, HERE << "disker will create in " << path);
        return;
    }

    debugs (47,3, HERE << "creating in " << path);

    struct stat dir_sb;
    if (::stat(path, &dir_sb) == 0) {
        struct stat file_sb;
        if (::stat(filePath, &file_sb) == 0) {
            debugs (47, DBG_IMPORTANT, "Skipping existing Rock db: " << filePath);
            return;
        }
        // else the db file is not there or is not accessible, and we will try
        // to create it later below, generating a detailed error on failures.
    } else { // path does not exist or is inaccessible
        // If path exists but is not accessible, mkdir() below will fail, and
        // the admin should see the error and act accordingly, so there is
        // no need to distinguish ENOENT from other possible stat() errors.
        debugs (47, DBG_IMPORTANT, "Creating Rock db directory: " << path);
        const int res = mkdir(path, 0700);
        if (res != 0) {
            debugs(47, DBG_CRITICAL, "Failed to create Rock db dir " << path <<
                   ": " << xstrerror());
            fatal("Rock Store db creation error");
        }
    }

    debugs (47, DBG_IMPORTANT, "Creating Rock db: " << filePath);
#if SLOWLY_FILL_WITH_ZEROS
    char block[1024];
    Must(maxSize() % sizeof(block) == 0);
    memset(block, '\0', sizeof(block));

    const int swap = open(filePath, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0600);
    for (off_t offset = 0; offset < maxSize(); offset += sizeof(block)) {
        if (write(swap, block, sizeof(block)) != sizeof(block)) {
            debugs(47, DBG_CRITICAL, "ERROR: Failed to create Rock Store db in " << filePath <<
                   ": " << xstrerror());
            fatal("Rock Store db creation error");
        }
    }
    close(swap);
#else
    const int swap = open(filePath, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0600);
    if (swap < 0) {
        debugs(47, DBG_CRITICAL, "ERROR: Failed to initialize Rock Store db in " << filePath <<
               "; create error: " << xstrerror());
        fatal("Rock Store db creation error");
    }

    if (ftruncate(swap, maxSize()) != 0) {
        debugs(47, DBG_CRITICAL, "ERROR: Failed to initialize Rock Store db in " << filePath <<
               "; truncate error: " << xstrerror());
        fatal("Rock Store db creation error");
    }

    char header[HeaderSize];
    memset(header, '\0', sizeof(header));
    if (write(swap, header, sizeof(header)) != sizeof(header)) {
        debugs(47, DBG_CRITICAL, "ERROR: Failed to initialize Rock Store db in " << filePath <<
               "; write error: " << xstrerror());
        fatal("Rock Store db initialization error");
    }
    close(swap);
#endif
}