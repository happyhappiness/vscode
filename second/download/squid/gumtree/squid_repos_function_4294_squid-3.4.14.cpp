long
Ssl::parse_flags(const char *flags)
{
    long fl = 0;
    char *tmp;
    char *flag;

    if (!flags)
        return 0;

    tmp = xstrdup(flags);

    flag = strtok(tmp, ":,");

    while (flag) {
        if (strcmp(flag, "NO_DEFAULT_CA") == 0)
            fl |= SSL_FLAG_NO_DEFAULT_CA;
        else if (strcmp(flag, "DELAYED_AUTH") == 0)
            fl |= SSL_FLAG_DELAYED_AUTH;
        else if (strcmp(flag, "DONT_VERIFY_PEER") == 0)
            fl |= SSL_FLAG_DONT_VERIFY_PEER;
        else if (strcmp(flag, "DONT_VERIFY_DOMAIN") == 0)
            fl |= SSL_FLAG_DONT_VERIFY_DOMAIN;
        else if (strcmp(flag, "NO_SESSION_REUSE") == 0)
            fl |= SSL_FLAG_NO_SESSION_REUSE;

#if X509_V_FLAG_CRL_CHECK

        else if (strcmp(flag, "VERIFY_CRL") == 0)
            fl |= SSL_FLAG_VERIFY_CRL;
        else if (strcmp(flag, "VERIFY_CRL_ALL") == 0)
            fl |= SSL_FLAG_VERIFY_CRL_ALL;

#endif

        else
            fatalf("Unknown ssl flag '%s'", flag);

        flag = strtok(NULL, ":,");
    }

    safe_free(tmp);
    return fl;
}