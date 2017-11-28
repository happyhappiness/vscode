static unsigned int
FileNameHashCached(const char *fname)
{
    static const char *lastFname = 0;
    static int lastHash = 0;
    // __FILE__ changes when we #include files
    if (lastFname != fname) { // cheap pointer comparison
        lastFname = fname;
        lastHash = TextException::FileNameHash(fname);
    }
    return lastHash;
}