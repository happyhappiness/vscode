bool
UFSSwapDir::verifyCacheDirs()
{
    if (!pathIsDirectory(path))
        return true;

    for (int j = 0; j < l1; j++) {
        char const *aPath = swapSubDir(j);

        if (!pathIsDirectory(aPath))
            return true;
    }

    return false;
}