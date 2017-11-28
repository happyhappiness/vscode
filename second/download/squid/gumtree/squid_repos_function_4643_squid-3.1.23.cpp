bool
UFSSwapDir::doubleCheck(StoreEntry & e)
{

    struct stat sb;

    if (::stat(fullPath(e.swap_filen, NULL), &sb) < 0) {
        debugs(47, 0, "UFSSwapDir::doubleCheck: MISSING SWAP FILE");
        dumpEntry(e);
        return true;
    }

    if ((off_t)e.swap_file_sz != sb.st_size) {
        debugs(47, 0, "UFSSwapDir::doubleCheck: SIZE MISMATCH");
        debugs(47, 0, "UFSSwapDir::doubleCheck: ENTRY SIZE: " << e.swap_file_sz << ", FILE SIZE: " << sb.st_size);
        dumpEntry(e);
        return true;
    }

    return false;
}