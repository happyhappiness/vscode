void
AuthNegotiateConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);
}