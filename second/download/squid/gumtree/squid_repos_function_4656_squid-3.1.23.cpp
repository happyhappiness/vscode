bool
UFSSwapDir::pathIsDirectory(const char *aPath)const
{

    struct stat sb;

    if (::stat(aPath, &sb) < 0) {
        debugs(47, 0, "" << aPath << ": " << xstrerror());
        return false;
    }

    if (S_ISDIR(sb.st_mode) == 0) {
        debugs(47, 0, "" << aPath << " is not a directory");
        return false;
    }

    return true;
}