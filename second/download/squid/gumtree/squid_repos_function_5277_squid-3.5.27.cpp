bool
Fs::Ufs::UFSSwapDir::doubleCheck(StoreEntry & e)
{

    struct stat sb;

    if (::stat(fullPath(e.swap_filen, NULL), &sb) < 0) {
        debugs(47, DBG_CRITICAL, HERE << "WARNING: Missing swap file");
        dumpEntry(e);
        return true;
    }

    if ((off_t)e.swap_file_sz != sb.st_size) {
        debugs(47, DBG_CRITICAL, HERE << "WARNING: Size Mismatch. Entry size: "
               << e.swap_file_sz << ", file size: " << sb.st_size);
        dumpEntry(e);
        return true;
    }

    return false;
}