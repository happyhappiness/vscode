ConfigOption *
CossSwapDir::getOptionTree() const
{
    ConfigOption *parentResult = SwapDir::getOptionTree();

    if (currentIOOptions == NULL)
        currentIOOptions = new ConfigOptionVector();

    currentIOOptions->options.push_back(parentResult);

    currentIOOptions->options.push_back(new ConfigOptionAdapter<CossSwapDir>(*const_cast<CossSwapDir *>(this), &CossSwapDir::optionIOParse, &CossSwapDir::optionIODump));

    currentIOOptions->options.push_back(
        new ConfigOptionAdapter<CossSwapDir>(*const_cast<CossSwapDir *>(this),
                                             &CossSwapDir::optionBlockSizeParse,
                                             &CossSwapDir::optionBlockSizeDump));


    ConfigOption *ioOptions = NULL;

    if (io)
        ioOptions = io->getOptionTree();

    if (ioOptions)
        currentIOOptions->options.push_back(ioOptions);

    ConfigOption* result = currentIOOptions;

    currentIOOptions = NULL;

    return result;
}