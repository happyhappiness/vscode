void
AuthNTLMConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);
}