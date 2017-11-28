ConfigOption *
UFSSwapDir::getOptionTree() const
{
    ConfigOption *parentResult = SwapDir::getOptionTree();

    if (currentIOOptions == NULL)
        currentIOOptions = new ConfigOptionVector();

    currentIOOptions->options.push_back(parentResult);

    currentIOOptions->options.push_back(new ConfigOptionAdapter<UFSSwapDir>(*const_cast<UFSSwapDir *>(this), &UFSSwapDir::optionIOParse, &UFSSwapDir::optionIODump));

    if (ConfigOption *ioOptions = IO->io->getOptionTree())
        currentIOOptions->options.push_back(ioOptions);

    ConfigOption* result = currentIOOptions;

    currentIOOptions = NULL;

    return result;
}