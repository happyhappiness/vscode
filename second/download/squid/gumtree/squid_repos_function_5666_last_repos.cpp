void
ACLMaxUserIP::parse()
{
    if (maximum) {
        debugs(28, DBG_IMPORTANT, "Attempting to alter already set User max IP acl");
        return;
    }

    char *t = ConfigParser::strtokFile();

    if (!t)
        return;

    debugs(28, 5, "aclParseUserMaxIP: First token is " << t);

    maximum = xatoi(t);

    debugs(28, 5, "aclParseUserMaxIP: Max IP address's " << maximum);

    return;
}