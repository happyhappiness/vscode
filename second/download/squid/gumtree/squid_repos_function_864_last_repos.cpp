static void
parse_access_log(CustomLog ** logs)
{
    const char *filename = ConfigParser::NextToken();
    if (!filename) {
        self_destruct();
        return;
    }

    CustomLog *cl = (CustomLog *)xcalloc(1, sizeof(*cl));

    cl->filename = xstrdup(filename);
    // default buffer size and fatal settings
    cl->bufferSize = 8*MAX_URL;
    cl->fatal = true;

    if (strcmp(filename, "none") == 0) {
        cl->type = Log::Format::CLF_NONE;
        aclParseAclList(LegacyParser, &cl->aclList, filename);
        while (*logs)
            logs = &(*logs)->next;
        *logs = cl;
        return;
    }

    cl->type = Log::Format::CLF_UNKNOWN;
    cl->rotateCount = -1; // default: use global logfile_rotate setting.

    const char *token = ConfigParser::PeekAtToken();
    if (!token) { // style #1
        // no options to deal with
    } else if (!strchr(token, '=')) { // style #3
        // if logformat name is recognized,
        // pop the previewed token; Else it must be an ACL name
        if (setLogformat(cl, token, false))
            (void)ConfigParser::NextToken();
    } else { // style #4
        do {
            if (strncasecmp(token, "on-error=", 9) == 0) {
                if (strncasecmp(token+9, "die", 3) == 0) {
                    cl->fatal = true;
                } else if (strncasecmp(token+9, "drop", 4) == 0) {
                    cl->fatal = false;
                } else {
                    debugs(3, DBG_CRITICAL, "Unknown value for on-error '" <<
                           token << "' expected 'drop' or 'die'");
                    xfree(cl->filename);
                    xfree(cl);
                    self_destruct();
                    return;
                }
            } else if (strncasecmp(token, "buffer-size=", 12) == 0) {
                parseBytesOptionValue(&cl->bufferSize, B_BYTES_STR, token+12);
            } else if (strncasecmp(token, "rotate=", 7) == 0) {
                cl->rotateCount = xatoi(token + 7);
            } else if (strncasecmp(token, "logformat=", 10) == 0) {
                setLogformat(cl, token+10, true);
            } else if (!strchr(token, '=')) {
                // Do not pop the token; it must be an ACL name
                break; // done with name=value options, now to ACLs
            } else {
                debugs(3, DBG_CRITICAL, "Unknown access_log option " << token);
                xfree(cl->filename);
                xfree(cl);
                self_destruct();
                return;
            }
            // Pop the token, it was a valid "name=value" option
            (void)ConfigParser::NextToken();
            // Get next with preview ConfigParser::NextToken call.
        } while ((token = ConfigParser::PeekAtToken()) != NULL);
    }

    // set format if it has not been specified explicitly
    if (cl->type == Log::Format::CLF_UNKNOWN)
        setLogformat(cl, "squid", true);

    aclParseAclList(LegacyParser, &cl->aclList, cl->filename);

    while (*logs)
        logs = &(*logs)->next;

    *logs = cl;
}