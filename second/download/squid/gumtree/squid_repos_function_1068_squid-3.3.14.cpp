static void
parse_http_header_access(HeaderManglers **pm)
{
    char *t = NULL;

    if ((t = strtok(NULL, w_space)) == NULL) {
        debugs(3, DBG_CRITICAL, "" << cfg_filename << " line " << config_lineno << ": " << config_input_line);
        debugs(3, DBG_CRITICAL, "parse_http_header_access: missing header name.");
        return;
    }

    if (!*pm)
        *pm = new HeaderManglers;
    HeaderManglers *manglers = *pm;
    headerMangler *mangler = manglers->track(t);
    assert(mangler);
    parse_acl_access(&mangler->access_list);
}