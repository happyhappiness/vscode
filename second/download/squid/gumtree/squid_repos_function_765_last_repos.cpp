static void
parse_http_header_replace(HeaderManglers **pm)
{
    char *t = NULL;

    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(3, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, DBG_CRITICAL, "parse_http_header_replace: missing header name.");
        return;
    }

    const char *value = ConfigParser::NextQuotedOrToEol();

    if (!*pm)
        *pm = new HeaderManglers;
    HeaderManglers *manglers = *pm;
    manglers->setReplacement(t, value);
}