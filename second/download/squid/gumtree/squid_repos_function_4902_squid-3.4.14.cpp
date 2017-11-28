void
Rock::SwapDir::reconfigure()
{
    parseSize(true);
    parseOptions(1);
    // TODO: can we reconfigure the replacement policy (repl)?
    validateOptions();
}