const char*
SkipBuildPrefix(const char* path)
{
    static const size_t BuildPrefixLength = BuildPrefixInit();

    return path+BuildPrefixLength;
}