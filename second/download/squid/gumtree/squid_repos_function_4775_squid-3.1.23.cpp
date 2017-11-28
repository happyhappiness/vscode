void
ACLMaxUserIP::parse()
{
    if (maximum) {
        debugs(28, 1, "Attempting to alter already set User max IP acl");
        return;
    }

    char *t = ConfigParser::strtokFile();

    if (!t)
        return;

    debugs(28, 5, "aclParseUserMaxIP: First token is " << t);

    if (strcmp("-s", t) == 0) {
        debugs(28, 5, "aclParseUserMaxIP: Going strict");
        flags.strict = 1;
        t = ConfigParser::strtokFile();
    }

    if (!t)
        return;

    maximum = xatoi(t);

    debugs(28, 5, "aclParseUserMaxIP: Max IP address's " << maximum);

    return;
}