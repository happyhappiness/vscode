void
ACLUserData::parse()
{
    debugs(28, 2, "parsing user list");

    char *t = NULL;
    if ((t = ConfigParser::strtokFile())) {
        SBuf s(t);
        debugs(28, 5, "first token is " << s);

        if (s.cmp("-i",2) == 0) {
            debugs(28, 5, "Going case-insensitive");
            flags.case_insensitive = true;
            // due to how the std::set API work, if we want to change
            // the comparison function we have to create a new std::set
            UserDataNames_t newUdn(CaseInsensitveSBufCompare);
            newUdn.insert(userDataNames.begin(), userDataNames.end());
            swap(userDataNames,newUdn);
        } else if (s.cmp("REQUIRED") == 0) {
            debugs(28, 5, "REQUIRED-type enabled");
            flags.required = true;
        } else {
            if (flags.case_insensitive)
                s.toLower();

            debugs(28, 6, "Adding user " << s);
            userDataNames.insert(s);
        }
    }

    debugs(28, 3, "Case-insensitive-switch is " << flags.case_insensitive);
    /* we might inherit from a previous declaration */

    debugs(28, 4, "parsing following tokens");

    while ((t = ConfigParser::strtokFile())) {
        SBuf s(t);
        debugs(28, 6, "Got token: " << s);

        if (flags.case_insensitive)
            s.toLower();

        debugs(28, 6, "Adding user " << s);
        userDataNames.insert(s);
    }

    if (flags.required && !userDataNames.empty()) {
        debugs(28, DBG_PARSE_NOTE(1), "WARNING: detected attempt to add usernames to an acl of type REQUIRED");
        userDataNames.clear();
    }

    debugs(28,4, "ACL contains " << userDataNames.size() << " users");
}