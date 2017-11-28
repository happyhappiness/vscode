void
Auth::Config::parse(Auth::Config * scheme, int, char *param_str)
{
    if (strcmp(param_str, "program") == 0) {
        if (authenticateProgram)
            wordlistDestroy(&authenticateProgram);

        parse_wordlist(&authenticateProgram);

        requirePathnameExists("Authentication helper program", authenticateProgram->key);

    } else if (strcmp(param_str, "realm") == 0) {
        realm.clear();

        char *token = ConfigParser::NextQuotedOrToEol();

        while (token && *token && xisspace(*token))
            ++token;

        if (!token || !*token) {
            debugs(29, DBG_PARSE_NOTE(DBG_IMPORTANT), "ERROR: Missing auth_param " << scheme->type() << " realm");
            self_destruct();
            return;
        }

        realm = token;

    } else if (strcmp(param_str, "children") == 0) {
        authenticateChildren.parseConfig();

    } else if (strcmp(param_str, "key_extras") == 0) {
        keyExtrasLine = ConfigParser::NextQuotedToken();
        Format::Format *nlf =  new ::Format::Format(scheme->type());
        if (!nlf->parse(keyExtrasLine.termedBuf())) {
            debugs(29, DBG_CRITICAL, "FATAL: Failed parsing key_extras formatting value");
            self_destruct();
            return;
        }
        if (keyExtras)
            delete keyExtras;

        keyExtras = nlf;

        if (char *t = strtok(NULL, w_space)) {
            debugs(29, DBG_CRITICAL, "FATAL: Unexpected argument '" << t << "' after request_format specification");
            self_destruct();
        }
    } else {
        debugs(29, DBG_CRITICAL, "Unrecognised " << scheme->type() << " auth scheme parameter '" << param_str << "'");
    }
}