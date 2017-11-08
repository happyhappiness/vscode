static int is_absolute_uri(char *uri)
{
    int i = strlen(uri);
    if (   (i > 7 && strncasecmp(uri, "http://",   7) == 0)
        || (i > 8 && strncasecmp(uri, "https://",  8) == 0)
        || (i > 9 && strncasecmp(uri, "gopher://", 9) == 0)
        || (i > 6 && strncasecmp(uri, "ftp://",    6) == 0)
        || (i > 5 && strncasecmp(uri, "ldap:",     5) == 0)
        || (i > 5 && strncasecmp(uri, "news:",     5) == 0)
        || (i > 7 && strncasecmp(uri, "mailto:",   7) == 0) ) {
        return 1;
    }
    else {
        return 0;
    }
}