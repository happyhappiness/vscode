void
AuthDigestConfig::done()
{
    if (authenticate)
        wordlistDestroy(&authenticate);

    safe_free(digestAuthRealm);
}