static void
parse_http_header_access(HeaderManglers **pm)
{
    char *t = NULL;

    if ((t = ConfigParser::NextToken()) == NULL) {
        debugs(3, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, DBG_CRITICAL, "parse_http_header_access: missing header name.");
        return;
    }

    if (!*pm)
        *pm = new HeaderManglers;
    HeaderManglers *manglers = *pm;
    headerMangler *mangler = manglers->track(t);
    assert(mangler);

    std::string directive = "http_header_access ";
    directive += t;
    aclParseAccessLine(directive.c_str(), LegacyParser, &mangler->access_list);
}