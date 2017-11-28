void
UFSSwapDir::changeIO(DiskIOModule *module)
{
    DiskIOStrategy *anIO = module->createStrategy();
    safe_free(ioType);
    ioType = xstrdup(module->type());

    delete IO->io;
    IO->io = anIO;
    /* Change the IO Options */

    if (currentIOOptions && currentIOOptions->options.size() > 2)
        delete currentIOOptions->options.pop_back();

    /* TODO: factor out these 4 lines */
    ConfigOption *ioOptions = IO->io->getOptionTree();

    if (ioOptions)
        currentIOOptions->options.push_back(ioOptions);
}