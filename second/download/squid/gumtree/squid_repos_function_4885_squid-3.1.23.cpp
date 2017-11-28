void
AuthBasicConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);

    if (basicAuthRealm)
        safe_free(basicAuthRealm);
}