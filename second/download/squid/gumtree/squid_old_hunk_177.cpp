    storeAppendPrintf(&sentry, "\n");
}

void
CossSwapDir::parse(int anIndex, char *aPath)
{
    unsigned int i;
    unsigned int size;
    off_t max_offset;

    i = GetInteger();
    size = i << 10;		/* Mbytes to Kbytes */

    if (size <= 0)
        fatal("storeCossDirParse: invalid size value");

    index = anIndex;

    path = xstrdup(aPath);

    max_size = size;

    parseOptions(0);

    if (NULL == io)
        changeIO(DiskIOModule::FindDefault());

