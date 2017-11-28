    storeAppendPrintf(&sentry, "\n");
}

void
CossSwapDir::parse(int anIndex, char *aPath)
{
    const int i = GetInteger();
    if (i <= 0)
        fatal("storeCossDirParse: invalid size value");

    index = anIndex;

    path = xstrdup(aPath);

    max_size = static_cast<uint64_t>(i) << 20; // MBytes to Bytes

    parseOptions(0);

    if (NULL == io)
        changeIO(DiskIOModule::FindDefault());

