void
Rock::SwapDir::parse(int anIndex, char *aPath)
{
    index = anIndex;

    path = xstrdup(aPath);

    // cache store is located at path/db
    String fname(path);
    fname.append("/rock");
    filePath = xstrdup(fname.termedBuf());

    parseSize(false);
    parseOptions(0);

    // Current openForWriting() code overwrites the old slot if needed
    // and possible, so proactively removing old slots is probably useless.
    assert(!repl); // repl = createRemovalPolicy(Config.replPolicy);

    validateOptions();
}