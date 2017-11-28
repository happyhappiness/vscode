static void
parse_access_log(CustomLog ** logs)
{
    CustomLog *cl = (CustomLog *)xcalloc(1, sizeof(*cl));

    // default buffer size and fatal settings
    cl->bufferSize = 8*MAX_URL;
    cl->fatal = true;

    /* determine configuration style */

    const char *filename = strtok(NULL, w_space);
    if (!filename) {
        self_destruct();
        return;
    }

    if (strcmp(filename, "none") == 0) {
        cl->type = Log::Format::CLF_NONE;
        aclParseAclList(LegacyParser, &cl->aclList, filename);
        while (*logs)
            logs = &(*logs)->next;
        *logs = cl;
        return;
    }

    cl->filename = xstrdup(filename);
    cl->type = Log::Format::CLF_UNKNOWN;

    const char *token = ConfigParser::strtokFile();
    if (!token) { // style #1
        // no options to deal with
    } else if (!strchr(token, '=')) { // style #3
        // if logformat name is not recognized,
        // put back the token; it must be an ACL name
        if (!setLogformat(cl, token, false))
            ConfigParser::strtokFileUndo();
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
                    self_destruct();
                }
            } else if (strncasecmp(token, "buffer-size=", 12) == 0) {
                parseBytesOptionValue(&cl->bufferSize, B_BYTES_STR, token+12);
            } else if (strncasecmp(token, "logformat=", 10) == 0) {
                setLogformat(cl, token+10, true);
            } else if (!strchr(token, '=')) {
                // put back the token; it must be an ACL name
                ConfigParser::strtokFileUndo();
                break; // done with name=value options, now to ACLs
            } else {
                debugs(3, DBG_CRITICAL, "Unknown access_log option " << token);
                self_destruct();
            }
        } while ((token = ConfigParser::strtokFile()) != NULL);
    }

    // set format if it has not been specified explicitly
    if (cl->type == Log::Format::CLF_UNKNOWN)
        setLogformat(cl, "squid", true);

    aclParseAclList(LegacyParser, &cl->aclList, cl->filename);

    while (*logs)
        logs = &(*logs)->next;

    *logs = cl;
}