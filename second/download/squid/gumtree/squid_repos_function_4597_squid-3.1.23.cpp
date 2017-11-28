void
CossSwapDir::changeIO(DiskIOModule *module)
{
    DiskIOStrategy *anIO = module->createStrategy();
    safe_free(ioModule);
    ioModule = xstrdup(module->type());

    delete io;
    io = anIO;
    /* Change the IO Options */

    if (currentIOOptions == NULL)
        currentIOOptions = new ConfigOptionVector();

    if (currentIOOptions->options.size() > 3)
        delete currentIOOptions->options.pop_back();

    /* TODO: factor out these 4 lines */
    ConfigOption *ioOptions = NULL;

    if (io)
        ioOptions = io->getOptionTree();

    if (ioOptions)
        currentIOOptions->options.push_back(ioOptions);
}