void
UFSSwapDir::parse (int anIndex, char *aPath)
{
    index = anIndex;
    path = xstrdup(aPath);

    parseSizeL1L2();

    /* Initialise replacement policy stuff */
    repl = createRemovalPolicy(Config.replPolicy);

    parseOptions(0);
}