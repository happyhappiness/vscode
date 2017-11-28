void
ESIVarState::buildVary (HttpReply *rep)
{
    char tempstr[1024];
    tempstr[0]='\0';

    if (flags.language)
        strcat (tempstr, "Accept-Language ");

    if (flags.cookie)
        strcat (tempstr, "Cookie ");

    if (flags.host)
        strcat (tempstr, "Host ");

    if (flags.referer)
        strcat (tempstr, "Referer ");

    if (flags.useragent)
        strcat (tempstr, "User-Agent ");

    if (!tempstr[0])
        return;

    String strVary (rep->header.getList (HDR_VARY));

    if (!strVary.size() || strVary[0] != '*') {
        rep->header.putStr (HDR_VARY, tempstr);
    }
}