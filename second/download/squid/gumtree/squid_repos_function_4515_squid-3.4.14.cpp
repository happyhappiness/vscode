void
ACLUserData::parse()
{
    debugs(28, 2, "aclParseUserList: parsing user list");
    char *t = NULL;

    if ((t = ConfigParser::strtokFile())) {
        debugs(28, 5, "aclParseUserList: First token is " << t);

        if (strcmp("-i", t) == 0) {
            debugs(28, 5, "aclParseUserList: Going case-insensitive");
            flags.case_insensitive = true;
        } else if (strcmp("REQUIRED", t) == 0) {
            debugs(28, 5, "aclParseUserList: REQUIRED-type enabled");
            flags.required = true;
        } else {
            if (flags.case_insensitive)
                Tolower(t);

            names = names->insert(xstrdup(t), splaystrcmp);
        }
    }

    debugs(28, 3, "aclParseUserList: Case-insensitive-switch is " << flags.case_insensitive);
    /* we might inherit from a previous declaration */

    debugs(28, 4, "aclParseUserList: parsing user list");

    while ((t = ConfigParser::strtokFile())) {
        debugs(28, 6, "aclParseUserList: Got token: " << t);

        if (flags.case_insensitive)
            Tolower(t);

        names = names->insert(xstrdup(t), splaystrcmp);
    }
}