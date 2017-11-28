bool
Ssl::ErrorIsOptional(const char *name)
{
    for (int i = 0; OptionalSslErrors[i] != NULL; ++i) {
        if (strcmp(name, OptionalSslErrors[i]) == 0)
            return true;
    }
    return false;
}