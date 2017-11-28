static void loadSslErrorMap()
{
    assert(TheSslErrors.empty());
    for (int i = 0; TheSslErrorArray[i].name; ++i) {
        TheSslErrors[TheSslErrorArray[i].value] = &TheSslErrorArray[i];
    }
}