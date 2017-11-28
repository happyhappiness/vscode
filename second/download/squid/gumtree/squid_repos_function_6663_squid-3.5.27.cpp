char *
ESIVariableUserAgent::getProductVersion (char const *s)
{
    char const *t;
    int len;
    t = index(s,'/');

    if (!t || !*(++t))
        return xstrdup("");

    len = strcspn(t, " \r\n()<>@,;:\\\"/[]?={}");

    return xstrndup(t, len + 1);
}