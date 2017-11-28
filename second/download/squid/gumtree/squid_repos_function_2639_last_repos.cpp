bool
TemplateFile::loadFor(const HttpRequest *request)
{
    String hdr;

#if USE_ERR_LOCALES
    if (loaded()) // already loaded?
        return true;

    if (!request || !request->header.getList(Http::HdrType::ACCEPT_LANGUAGE, &hdr) )
        return false;

    char lang[256];
    size_t pos = 0; // current parsing position in header string

    debugs(4, 6, HERE << "Testing Header: '" << hdr << "'");

    while ( strHdrAcptLangGetItem(hdr, lang, 256, pos) ) {

        /* wildcard uses the configured default language */
        if (lang[0] == '*' && lang[1] == '\0') {
            debugs(4, 6, HERE << "Found language '" << lang << "'. Using configured default.");
            return false;
        }

        debugs(4, 6, HERE << "Found language '" << lang << "', testing for available template");

        if (tryLoadTemplate(lang)) {
            /* store the language we found for the Content-Language reply header */
            errLanguage = lang;
            break;
        } else if (Config.errorLogMissingLanguages) {
            debugs(4, DBG_IMPORTANT, "WARNING: Error Pages Missing Language: " << lang);
        }
    }
#endif

    return loaded();
}